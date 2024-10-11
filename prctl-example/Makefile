CC = gcc
CFLAGS = -Wall -Wextra -fPIC -I./include
LDFLAGS = -shared
LIB_NAME = libprctl_lib.so

# Targets
all: $(LIB_NAME) main

$(LIB_NAME): src/prctl_lib.o
	$(CC) $(LDFLAGS) -o $@ $^

src/prctl_lib.o: src/prctl_lib.c include/prctl_lib.h
	$(CC) $(CFLAGS) -c src/prctl_lib.c -o src/prctl_lib.o

main: src/main.o $(LIB_NAME)
	$(CC) src/main.o -L. -lprctl_lib -o main

src/main.o: src/main.c include/prctl_lib.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

clean:
	rm -f src/*.o main $(LIB_NAME)

.PHONY: all clean

