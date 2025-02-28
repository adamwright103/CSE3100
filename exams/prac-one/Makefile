CC := gcc
CFLAGS := -g -Wall -std=c99
TARGETS := squares calculator

all: $(TARGETS)
squares: squares.c
	$(CC) $(CFLAGS) -o $@ $^

calculator: calculator.c linkedlist.c linkedlist.h 
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -rf *.o *.exe $(TARGETS)