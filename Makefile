CC = g++

CompileParms = -Wall -Werror -pedantic -std=c++11 -g -c

OBJS = Checkers.o

checkers: $(OBJS)
	$(CC) $(OBJS) -o Checkers

clean:
	rm -f Checkers Checkers.o