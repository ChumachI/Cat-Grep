CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11 -g
TARGET = s21_grep

all: $(TARGET)

$(TARGET): clean
	$(CC) $(CFLAGS) -o $(TARGET) grep.c

clean:
	rm -f $(TARGET)