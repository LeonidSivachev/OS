# OWN OPERATION SYSTEM
## kernel
Hello world kernel that was wrote with cross-compiler  
src: source file 
builder: script to build project
### to build iso
./builder
## os
kernel: sorce of os kernel
libc: source of c libraury 
### to build iso
change in default-host.sh and default-compilerpath.sh path to cross-compiler
./iso.sh
### to clean
./clean.sh (will delete all except src and shell scripts)