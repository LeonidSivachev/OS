DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

#CFLAGS?=-O2 -g 
CFLAGS?=-O0 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/boot/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/kernel.o \

OBJS=\
$(ARCHDIR)/boot/crti.o \
$(ARCHDIR)/boot/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/boot/crtend.o \
$(ARCHDIR)/boot/crtn.o \

LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/boot/crti.o \
$(ARCHDIR)/boot/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ARCHDIR)/boot/crtend.o \
$(ARCHDIR)/boot/crtn.o \


SOURCE_KERNEL_OBJ=\
arch/i386/gdt/gdt.o \
arch/i386/gdt/gdt_flush.o \
kernel/multiboot/multiboot.o \
arch/i386/idt/idt.o \
arch/i386/idt/exeptions.o \
arch/i386/idt/ports.o \
arch/i386/idt/pic.o \
arch/i386/idt/keyboard/keyboard_handler.o \
arch/i386/idt/keyboard/kbrd_handler.o \

TEST_COMPILE_FILES=\

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: myos.kernel

myos.kernel: $(OBJS) $(ARCHDIR)/boot/linker.ld $(TEST_COMPILE_FILES)
	$(CC) -T $(ARCHDIR)/boot/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot2 myos.kernel

$(ARCHDIR)/boot/crtbegin.o $(ARCHDIR)/boot/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

kernel/kernel.o : kernel/kernel.c $(SOURCE_KERNEL_OBJ)
	$(CC) -MD -c kernel/kernel.c -o kernel/kernel_tmp.o -std=gnu11 $(CFLAGS) $(CPPFLAGS)
	$(CC) -nostdlib -r -o kernel/kernel.o kernel/kernel_tmp.o $(SOURCE_KERNEL_OBJ)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS) -I.

.s.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

%.o: %.asm
	$(AS) -f elf32 $< -o $@

clean:
	rm -f myos.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d
	rm -f $(SOURCE_KERNEL_OBJ) *.o */*.o */*/*.o
	rm -f $(SOURCE_KERNEL_OBJ:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: myos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp myos.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
