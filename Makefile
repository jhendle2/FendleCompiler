compile:
	gcc -g -Wall -o fdlc main.c tokenizer.c parser.c

all: fdlc input.fdl
	gcc -g -Wall -o fdlc main.c tokenizer.c parser.c
	./fdlc input.fdl
	
test:
	gcc -g -Wall -o fdlc main.c tokenizer.c parser.c
	./fdlc testcode.fdl