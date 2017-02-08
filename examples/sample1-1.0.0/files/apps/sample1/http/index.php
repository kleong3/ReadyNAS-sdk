<html>
<head><title>Sample1</title></head>
<style type="text/css">
table, td, th {
  border: 1px solid #000000;
  border-spacing: 0px;
  border-collapse: collapse;
  margin: 20px;
  padding: 2px;
  empty-cells: show;
  text-align: left;
  font-size: 10pt;
}

table.dbtbl tr:hover {
  background: #ccddee;
}

table.dbtbl tr:hover td:hover {
  background: #cceedd;
}
</style>
<body>
<h1>This is <b>sampel1</b> application page.</h1>
<?php print "<a href=\"https://" . $_SERVER["SERVER_ADDR"] . "/apps/sample1/config.html\">Config</a>"; ?>    
<p>You may need start your service using dashboard framework before you see something in below.</p>
<?php
try {
  $db = new SQLite3("/apps/sample1/db.sq3");
  if ($db) {
    $result = $db->query("SELECT * FROM log");
    $ncol = $result->numColumns();
    print '<table class="dbtbl">';
    print '<tr><th>user</th><th>system</th><th>idle</th><th>iowait</th></tr>';
    while ($row = $result->fetchArray()) {
      print "<tr><td>$row[user]</td><td>$row[system]</td><td>$row[idle]</td><td>$row[iowait]</td></tr>";
    }
    print "</table>\n";
    $result->finalize();
    $db->close();
  }
  else {
    print "Service never ran.";
  }
}
catch (Exception $e) {
  print "Caught error";
}
?>
</body>
</html>
