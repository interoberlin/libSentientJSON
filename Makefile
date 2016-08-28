
CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -g
LD = gcc
LDFLAGS = -lgcc

clean:
	rm *.o

all: test

test: test.o json.o
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c %s
	$(CC) $(CFLAGS) -c $< -o $@
