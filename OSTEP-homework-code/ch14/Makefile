PROGS =	null

all:	$(PROGS)

%:	%.c
	$(CC) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o