 CC = gcc
 CFLAGS = -Wall -Wextra -std=c99
 TARGET = redactor
 OBJECTS = main.o red.o

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

test: $(TARGET)
	echo "old line" > input.txt
		./$(TARGET) input.txt 's/old/new/'
			./$(TARGET) input.txt '/new/d'
				./$(TARGET) input.txt 's/^/prefix /'
					./$(TARGET) input.txt 's/ suffix/new_suffix/'
