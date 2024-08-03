CC = aarch64-linux-gnu-gcc
CFLAGS = -Wall -O2
TARGET = main
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
