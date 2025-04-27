KBRD_SRC=tmr.o \
tmr_handler.o \

.PHONY: all clean 
.SUFFIXES: .o .c .S .asm

all : timer.o

timer.o : $(KBRD_SRC)
	$(CC) -nostdlib -r -o timer.o $(KBRD_SRC)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.s.o:
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

-include tmr.d