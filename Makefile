CC = gcc
CFLAGS = -g -Wall -Wextra
CFLAGS_BFD = -lbfd
OBJS = gtrace.o option_handle.o environ_handle.o elf_analyze.o



gtrace: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(CFLAGS_BFD)
	$(CC) $(CFLAGS) -fPIE -pie -o sample sample.c
	$(CC) $(CFLAGS) -o loop loop.c
	$(CC) $(CFLAGS) -o test test.c -lelf

gtrace.o: gtrace.c
	$(CC) $(CFLAGS) -c $<

option_handle.o: option_handle.c
	$(CC) $(CFLAGS) -c $<

environ_handle.o: environ_handle.c
	$(CC) $(CFLAGS) -c $<

elf_analyze.o: elf_analyze.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
	rm -f gtrace
	rm -f sample
	rm -f loop
	rm -f test
