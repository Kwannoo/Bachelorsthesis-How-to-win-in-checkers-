CC = g++

CompileParms = -Wall -Werror -pedantic -std=c++11 -g -c

OBJS = Checkers.o

aitetris: $(OBJS)
	$(CC) $(OBJS) -o Checkers

clean:
	rm -f Checkers Checkers.o