CC := gcc
CFLAGS := -g -Wall -Wextra

gtrace: gtrace.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o
	rm -f gtrace
