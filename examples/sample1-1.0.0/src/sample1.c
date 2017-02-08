#include <stdio.h>
#include <stdarg.h>
#include <sqlite3.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
//#include <fcntl.h>
#include <errno.h>
#include <libxml/tree.h>
#include <systemd/sd-daemon.h>


const char* const SQ3FILE = "/apps/sample1/db.sq3";
const char* const CONFFILE = "/apps/sample1/sample1.conf";

static void __attribute__((format(printf,3,4)))
mylog(const char* fname, int lineno, const char* fmt, ...)
{
  fprintf(stderr, "%s:%d ", fname, lineno);

  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);

  return;
}

static sqlite3*
open_db(int create)
{
  sqlite3* db;

  sqlite3_config(SQLITE_CONFIG_SERIALIZED);
  int sq3rc = sqlite3_open_v2(SQ3FILE,
                              &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_FULLMUTEX | (create ? SQLITE_OPEN_CREATE : 0),
                              NULL);
  if (SQLITE_OK == sq3rc)
    return db;

  mylog(__FILE__, __LINE__, "Fail to open db. (sq3rc=%d)\n", sq3rc);
  return NULL;
}

static int
close_db(sqlite3 *db)
{
  return sqlite3_close(db);
}

static int
sql_exec(sqlite3* db, const char* fname, int lineno, const char* sql)
{
  int sq3rc = SQLITE_OK;
  char* emsg = NULL;
  sq3rc = sqlite3_exec(db, sql, 0, 0, &emsg);
  if (sq3rc!=SQLITE_OK && sq3rc!=SQLITE_BUSY && sq3rc!=SQLITE_LOCKED) {
    mylog(fname, lineno, "Error sql=%s ==> sq3rc=%d emsg=%s\n", sql, sq3rc, emsg);
  }
  if (emsg)
    sqlite3_free(emsg);
  return sq3rc;
}

static int
sql_exec_mprintf(sqlite3* db, const char* fname, int lineno,
                 const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  char* sql = sqlite3_vmprintf(fmt, ap);
  va_end(ap);

  int sq3rc = sql_exec(db, fname, lineno, sql);
  if (sq3rc!=SQLITE_OK)
    mylog(fname, lineno, "SQL=%s ==> %d\n", sql, sq3rc);
  if (sql)
    sqlite3_free(sql);
  return sq3rc;
}

static int
init_db(void)
{
  sqlite3* db = open_db(1);
  if (!db)
    return ENOENT;

  if (SQLITE_OK !=
      sql_exec_mprintf(db, __FILE__, __LINE__,
                       "DROP TABLE IF EXISTS `log`;"
                       "CREATE TABLE `log`"
                       """(ts DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP"
                       """,user BIGINT NOT NULL"
                       """,nice BIGINT NOT NULL"
                       """,system BIGINT NOT NULL"
                       """,idle BIGINT NOT NULL"
                       """,iowait BIGINT NOT NULL"
                       ")")) {
    return ENOENT;
  }
  close_db(db);
  return 0;
}

static void
update_db(void)
{
  sqlite3* db = open_db(0);
  if (!db)
    return;

  FILE* fp = fopen("/proc/stat", "rb");
  if (fp) {
    uint64_t v_user, v_nice, v_system, v_idle, v_iowait;
    if (5==fscanf(fp, "cpu %"SCNu64" %"SCNu64" %"SCNu64" %"SCNu64" %"SCNu64" %*[^\n]%*c",
                  &v_user, &v_nice, &v_system, &v_idle, &v_iowait)) {
      (void) sql_exec_mprintf(db, __FILE__, __LINE__,
                              "INSERT INTO `log`"
                              " (user,nice,system,idle,iowait)"
                              " VALUES(%"PRIu64",%"PRIu64",%"PRIu64",%"PRIu64",%"PRIu64")",
                              v_user, v_nice, v_system, v_idle, v_iowait);
    }
    fclose(fp);
  }
  close_db(db);
}

struct conf {
  int interval;
};

static void
read_config(struct conf* conf)
{
  xmlDocPtr xmldoc = NULL;
  xmlNodePtr root_node = NULL;

  xmlInitParser();
  xmlKeepBlanksDefault(0);

  // clear
  memset(conf, 0, sizeof(*conf));

  // set defaujlt
  conf->interval = 60;

  if ((xmldoc = xmlReadFile(CONFFILE, "utf-8", 0 /*XML_PARSE_RECOVER*/)) &&
      (root_node = xmlDocGetRootElement(xmldoc))) {
    for (xmlNode* node = root_node->children;
         node;
         node = node->next) {
      if (!strcmp((char*)node->name, "Interval")) {
        conf->interval = node->children && node->children->content ? atoi((char*)node->children->content) : 60;
      }
    }
  }

  if (xmldoc)
    xmlFreeDoc(xmldoc);
}

int
main(int argc, char** argv)
{
  int rc;
  struct conf conf;

  (void) argc;
  (void) argv;

  sd_notify(0, "STATUS=Intializing");

  if ((rc = init_db()))
    return rc;

  sd_notify(0, "STATUS=Configuring");
  read_config(&conf);

  // emulate slow startup
  for (int i=2; i<100; i++) {
    sd_notifyf(0, "STATUS=Downloading %d%%", i);
    sleep(1);
  }
  sd_notifyf(0, "READY=1\nSTATUS=Initialization completed\nMAINPID=%lu", (unsigned long)getpid());

  mylog(__FILE__, __LINE__, "Start fvapp-sample1(interval=%d)\n", conf.interval);

  while (1) {
    update_db();
    sleep(conf.interval);
  }
  return 0;
}
