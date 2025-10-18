KBRD_SRC=kbrd_driver.o \
#kbrd_handler.o \

OBJS = kbrd_driver.o

.PHONY: all clean 
.SUFFIXES: .o .c .S .asm

all : kbrd.o

kbrd.o : $(KBRD_SRC)
	$(CC) -nostdlib -r -o kbrd.o $(KBRD_SRC)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

-include kbrd_driver.d