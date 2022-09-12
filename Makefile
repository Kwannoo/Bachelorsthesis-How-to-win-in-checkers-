
INC_DIR = ./include
SRC_DIR = ./src
SOURCES = $(shell find $(SRC_DIR)/ -name 'main.cc')
OBJECTS = $(SOURCES:.c=.o)
TARGET  = Checkers
CC 		= g++ -Wall -g


.PHONY: all clean
all:$(TARGET)
clean:
	rm -f $(TARGET)
rebuild: clean all

$(TARGET): $(OBJECTS)
	$(CC)  -o $@ $^
%.o: %.c
	$(CC) -o $@ -c $<
