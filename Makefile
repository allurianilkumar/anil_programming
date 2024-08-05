CC = gcc
CFLAGS = -Wall -g

all: main

main: main.o lexer.o parser.o interpreter.o
	$(CC) $(CFLAGS) -o main main.o lexer.o parser.o interpreter.o

main.o: main.c lexer.h parser.h interpreter.h
	$(CC) $(CFLAGS) -c main.c

lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c parser.h lexer.h
	$(CC) $(CFLAGS) -c parser.c

interpreter.o: interpreter.c interpreter.h parser.h
	$(CC) $(CFLAGS) -c interpreter.c

clean:
	rm -f *.o main
