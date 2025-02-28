CC=gcc
CFLAGS=-Wall -g -std=c99
TARGETS=linked_list freq 

all: $(TARGETS)

freq: freq.c freq_helper.c
	$(CC) $(CFLAGS) -o freq freq.c freq_helper.c

linked_list: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *~ $(TARGETS) a.out
