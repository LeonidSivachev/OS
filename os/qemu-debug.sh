#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom myos.iso -serial stdio -d int,cpu_reset -no-reboot -s -S
#gdb -ex "target remote localhost:1234" -ex "symbol-file myos.kernel"