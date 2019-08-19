CC = gcc
CFLAGS = -g -Wall -Wextra

OBJS = gtrace.o option_handle.o


gtrace: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	$(CC) $(CFLAGS) -fPIE -pie -o sample sample.c
	$(CC) $(CFLAGS) -o loop loop.c

gtrace.o: gtrace.c
	$(CC) $(CFLAGS) -c $<

option_handle.o: option_handle.c
	$(CC) $(CFLAGS) -c $<



clean:
	rm -f *.o
	rm -f gtrace
	rm -f sample
