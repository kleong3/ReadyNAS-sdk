<?php
        foreach($_GET as $key=>$val) {
          if ($val) {
            system("rn_nml -a shareUsedBy:$key=sample3 >/dev/null");
          }
          else {
            system("rn_nml -d shareUsedBy:$key=sample3 >/dev/null");
          }
        }
        system("systemctl restart smb >/dev/null");
?>
