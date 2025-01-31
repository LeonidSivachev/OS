SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export COMPILE=${COMPILE:-$(./default-compilerpath.sh)}

#export AR=${HOST}-ar
#export AS=${HOST}-as
#export CC=${HOST}-gcc

#export AR=~/SysProject/opt/cross/bin/${HOST}-ar
#export AS=~/SysProject/opt/cross/bin/${HOST}-as
#export CC=~/SysProject/opt/cross/bin/${HOST}-gcc

export AR=${COMPILE}/${HOST}-ar
export AS=${COMPILE}/${HOST}-as
export CC=${COMPILE}/${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'
export CPPFLAGS=''

# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi
