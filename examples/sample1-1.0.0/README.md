### sample1: CPU usage recorder
#### Files in sample1
Below is a list of the files in sample1.

```
sample1-1.0.0/
sample1-1.0.0/debian
sample1-1.0.0/debian/postinst
sample1-1.0.0/debian/source
sample1-1.0.0/debian/source/format
sample1-1.0.0/debian/postrm
sample1-1.0.0/debian/copyright
sample1-1.0.0/debian/README
sample1-1.0.0/debian/changelog
sample1-1.0.0/debian/control
sample1-1.0.0/debian/rules
sample1-1.0.0/debian/compat
sample1-1.0.0/debian/prerm
sample1-1.0.0/debian/docs
sample1-1.0.0/debian/dirs
sample1-1.0.0/debian/sample1.lintian-overrides
sample1-1.0.0/debian/travis.yml
sample1-1.0.0/files
sample1-1.0.0/files/apps
sample1-1.0.0/files/apps/sample1
sample1-1.0.0/files/apps/sample1/http
sample1-1.0.0/files/apps/sample1/http/index.php
sample1-1.0.0/files/apps/sample1/https.conf
sample1-1.0.0/files/apps/sample1/http.conf
sample1-1.0.0/files/apps/sample1/web
sample1-1.0.0/files/apps/sample1/web/config.html
sample1-1.0.0/files/apps/sample1/web/set-config.php
sample1-1.0.0/files/apps/sample1/web/config.js
sample1-1.0.0/files/apps/sample1/web/jquery-1.8.3.min.js
sample1-1.0.0/files/apps/sample1/logo.png
sample1-1.0.0/files/apps/sample1/fvapp-sample1.service
sample1-1.0.0/files/apps/sample1/config.xml
sample1-1.0.0/README.NETGEAR
sample1-1.0.0/Makefile
sample1-1.0.0/src
sample1-1.0.0/src/Makefile
sample1-1.0.0/src/sample1.c
```
#### Apache Config
Apache config will be generated when you start Apache by systemd. You need to add `systemctl restart apache2.service` in your `postinst` file.

Depending on whether `web`, `http.conf`, and `https.conf` exist, Apache will be configured as below.

Some alias are created as below.

| url path | file system path | Note |
|----------|------------------|------|
| https://nas/apps/[AppName]  | /apps/[AppName]/web | If `web` folder exists.|
| https://nas/apps/logo/[AppName].png | /apps/[AppName]/logo.png | If `logo.png` file exists. |
#### Steps to build (both armel and amd64)
The commands below create `examples/sample_1.0.0_amd64.deb` and `examples/sample_1.0.0_armel.deb`. Specifically, the second line generates `amd64` and the third line generates `armel`. It is out of the scope of this document to explain Debian packaging steps. For more information about Debian packaging, please refer the Debian website.

**NOTE**: `ARCH` is preserved through `schroot` by the `-p` option and `ARCH` is preserved through `debuild` by the `-e ARCH` option. Eventually `ARCH` is used in `Makefile` to set various env. `ARCH` is not standard Debian but depends on the `Makefile` contained in the example. There may be a better way of doing this, so it is not necessary to follow this convention for your app development. For more information about Debian packaging, please see internet resources, such as [Debian Maintainers' Guide](http://www.debian.org/doc/manuals/maint-guide/build.en.html "Debian Maintainers' Guide").

```
$ cd examples/sample1-1.0.0
$ schroot -c R6 debuild -- -uc -us -B                                  ... for _amd64.deb
$ ARCH=arm schroot -p -c R6 debuild -- -e ARCH -uc -us -B -aarmel      ... for _armel.deb
```
