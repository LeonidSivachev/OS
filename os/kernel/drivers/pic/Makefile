PIC_SRC=pic_driver.o \
ports.o \

.PHONY: all, clean 
.SUFFIXES: .o .c .S .asm

all : pic.o

pic.o : $(PIC_SRC)
	$(CC) -nostdlib -r -o pic.o $(PIC_SRC)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.asm.o: FORCE
	$(AS) -f elf32 $< -o $@

clean:
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d