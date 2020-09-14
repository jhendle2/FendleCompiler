compile:
	gcc -g -Wall -o main main.c tokenizer.c parser.c

all:
	gcc -g -Wall -o main main.c tokenizer.c parser.c
	./main