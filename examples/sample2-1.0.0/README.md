### sample2: Dummy example (arch independent)
#### Files in sample2
Below is list of the files in sample2.

```
sample2-1.0.0/
sample2-1.0.0/debian
sample2-1.0.0/debian/postinst
sample2-1.0.0/debian/source
sample2-1.0.0/debian/source/format
sample2-1.0.0/debian/postrm
sample2-1.0.0/debian/copyright
sample2-1.0.0/debian/changelog
sample2-1.0.0/debian/control
sample2-1.0.0/debian/rules
sample2-1.0.0/debian/compat
sample2-1.0.0/debian/docs
sample2-1.0.0/files
sample2-1.0.0/files/apps
sample2-1.0.0/files/apps/sample2
sample2-1.0.0/files/apps/sample2/default-config
sample2-1.0.0/files/apps/sample2/https.conf
sample2-1.0.0/files/apps/sample2/http.conf
sample2-1.0.0/files/apps/sample2/web
sample2-1.0.0/files/apps/sample2/web/config.html
sample2-1.0.0/files/apps/sample2/web/index.html
sample2-1.0.0/files/apps/sample2/web/phpinfo.php
sample2-1.0.0/files/apps/sample2/logo.png
sample2-1.0.0/files/apps/sample2/config.xml
sample2-1.0.0/README.NETGEAR
sample2-1.0.0/Makefile
```
#### Steps to build (all)
The command below creates `examples/sample_2.0.0_all.deb`. This example is architecture independent, thus suffix is `_all`. It is out of the scope of this document to explain Debian packaging steps. For more information about Debian packaging, please refer the Debian website.

```
$ cd examples/sample2-1.0.0
$ schroot -c R6 debuild -- -uc -us -A       ... for _all.deb
```
#### Clean up
This command cleans work files, but doesn't clean `.deb` file and other outputs.

```
$ cd examples/sample2-1.0.0
$ schroot -c R6 dh -- clean
```
#### Clean everything
This command cleans work files and output files.

```
$ cd examples/sample2-1.0.0
$ schroot -c R6 make -- veryclean
```
