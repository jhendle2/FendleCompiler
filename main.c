#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"

int main(){
	char buffer[255];
	read_file("testcode.txt", buffer);
	//printf("%s",buffer);
	token* anchor = tokenize(buffer);
	print_tokens(anchor);
	return 0;
}