CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11
TARGET = s21_cat

all: $(TARGET)

$(TARGET): clean
	$(CC) $(CFLAGS) -o $(TARGET) cat.c

clean:
	rm -f $(TARGET)