CFLAGS=-Wall -g
OBJS=zobrist.o board.o hash.o

all:	15puzzle

15puzzle:	$(OBJS) main.o constants.h
	$(CC) $(CFLAGS) $(OBJS) main.o -o 15puzzle

main.o: constants.h zobrist.h board.h hash.h main.c
	$(CC) $(CFLAGS) -c main.c

zobrist.o: constants.h zobrist.h zobrist.c
	$(CC) $(CFLAGS) -c zobrist.c

board.o: constants.h board.h zobrist.h board.c
	$(CC) $(CFLAGS) -c board.c

hash.o: constants.h board.h zobrist.h hash.h hash.c
	$(CC) $(CFLAGS) -c hash.c

test: $(OBJS) constants.h test.c
	$(CC) $(CFLAGS) -c test.c
	$(CC) $(CFLAGS) $(OBJS) test.o -o 15puzzle_test
	./15puzzle_test

clean:
	rm -f *.o 15puzzle 15puzzle_test
