<?php
$interval = $_GET['interval'];
if ($interval < 1) {
   header("HTTP/1.1 500 Internal Server Error");
   echo "Invalid interval=$interval";
}
else {       
     system("/usr/bin/rn_nml -K sample1");
     $fp = fopen("/apps/sample1/sample1.conf", "w");
     fprintf($fp, "<Configuration>\n");
     fprintf($fp, "  <Interval>%d</Interval>\n", $interval);
     fprintf($fp, "</Configuration>\n");
     fclose($fp);
     system("/usr/bin/rn_nml -S sample1");
}
?>
