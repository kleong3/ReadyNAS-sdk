### Sample2: Example with Samba VFS module (arch independent)
#### Files in sample3
Below is list of the files in sample3.

```
sample3-1.0.0/
sample3-1.0.0/debian
sample3-1.0.0/debian/postinst
sample3-1.0.0/debian/source
sample3-1.0.0/debian/source/format
sample3-1.0.0/debian/postrm
sample3-1.0.0/debian/copyright
sample3-1.0.0/debian/README
sample3-1.0.0/debian/changelog
sample3-1.0.0/debian/control
sample3-1.0.0/debian/rules
sample3-1.0.0/debian/compat
sample3-1.0.0/debian/docs
sample3-1.0.0/files
sample3-1.0.0/files/apps
sample3-1.0.0/files/apps/sample3
sample3-1.0.0/files/apps/sample3/https.conf
sample3-1.0.0/files/apps/sample3/etc
sample3-1.0.0/files/apps/sample3/etc/samba.include.x86_64
sample3-1.0.0/files/apps/sample3/etc/samba.include.arm
sample3-1.0.0/files/apps/sample3/web
sample3-1.0.0/files/apps/sample3/web/config.html
sample3-1.0.0/files/apps/sample3/web/set-audit.php
sample3-1.0.0/files/apps/sample3/web/config.js
sample3-1.0.0/files/apps/sample3/web/jquery-1.8.3.min.js
sample3-1.0.0/files/apps/sample3/web/get-shares.php
sample3-1.0.0/files/apps/sample3/logo.png
sample3-1.0.0/files/apps/sample3/config.xml
sample3-1.0.0/README.NETGEAR
sample3-1.0.0/Makefile
```
#### Steps to build (all)
The command below creates `examples/sample_3.0.0_all.deb`. This example is architecture independent, thus suffix is `_all`. It is out of the scope of this document to explain Debian packaging steps. For more information about Debian packaging, please refer the Debian website.

```
$ cd examples/sample3-1.0.0
$ schroot -c R6 debuild -- -uc -us -A       ... for _all.deb
```
#### Clean up
This command cleans work files, but doesn't clean .deb file and other outputs.

```
$ cd examples/sample3-1.0.0
$ schroot -c R6 dh -- clean
```
#### Clean everything
This command cleans work files and output files.

```
$ cd examples/sample3-1.0.0
$ schroot -c R6 make -- veryclean
```
