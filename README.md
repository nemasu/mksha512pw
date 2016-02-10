# mksha512pw
Tool to create SHA512 shadow style passwords.

Build
=======

`make` for release version.

`make debug` to include debug symbols.

`make static` for static binary.

`make install` will put binary in /usr/bin.

Usage
=======

* Run `mksha512pw` and enter password twice.

* Pipe password:

 `echo "p@ssw0rd" | mksha512pw`
