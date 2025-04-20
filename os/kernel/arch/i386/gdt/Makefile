GDT_SRC=gdt_flush.o \
gdt_table.o \

.PHONY: all, clean 
.SUFFIXES: .o .c .S

all : gdt.o

gdt.o : $(GDT_SRC)
	$(CC) -nostdlib -r -o gdt.o $(GDT_SRC)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.s.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

-include gdt_table.d