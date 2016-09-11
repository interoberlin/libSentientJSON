
CC = colorgcc
CFLAGS = -std=gnu99 -Wall -Wextra -Wwrite-strings -g
CFLAGS += -I jasmine/
LD = gcc
LDFLAGS = -lgcc

all: test

test: test.o callbacks.o sentient_json.o jasmine/jsmn.o
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f jasmine/jsmn.o
