sample 1 contains the annotated version of the debian files which are applicable to both sample 2 and 3.


For information on the other files:https://github.com/ReadyNAS/sdk/wiki/ReadyNAS-Applications-Specification

An extremely helpful link with more in-depth information: https://wiki.debian.org/Packaging

A good reference on github: https://github.com/Mhynlo/rn-couchpotato

#### Clean up
This command cleans work files, but doesn't clean `.deb` file and other outputs.

```
$ cd examples/sample1-1.0.0
$ schroot -c R6 dh -- clean
```
#### Clean everything
This command cleans work files and output files.

```
$ cd examples/sample1-1.0.0
$ schroot -c R6 make -- veryclean
```
#### Debugging
Go to your readyNAS homepage and turn on ssh. This command will display the logs of your readyNAs.
```
$ ssh root@your-readyNAS-IP-Address
$ journalctl -af
```
Additionally, this command will display the status of the program on your device as well as more thorough errors.
```
$ ssh root@your-readyNAS-IP-Address
$ systemctl status fvapp-programName.service
```
Errors with the post/pre inst/rm files? The journal command for the root will only notify you of an error with the script,
not the line specifics. Change the first line of code to the command below to turn the file
into a bash script that can be run separately.
```
#!/bin/bash
```
And run the following command in a new terminal to pinpoint where the error is.
```
$ bash ~/path/to/scriptname
```
#### Permissions
The following code changes permissions of files/folders, making them accessible.
```
$ chmod u+x scriptname
```

