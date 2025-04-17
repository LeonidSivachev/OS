IDT_SRC=exeptions.o \
idt_exeptions.o \

.PHONY: all, clean 
.SUFFIXES: .o .c .S .asm

all : idt.o

idt.o : $(IDT_SRC)
	$(CC) -nostdlib -r -o idt.o $(IDT_SRC)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.asm.o:
	$(AS) -f elf32 $< -o $@

clean:
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d