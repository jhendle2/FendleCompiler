#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"

// fdlc FILE_NAME 

int main(int argc, char** argv){
	char buffer[255];
	
	if(argc<2){
		printf("[Interpret Error]: No input file! Use format:\n\tfdlc \"file.fdl\"\n");
		exit(1);
	}
	
	printf(".. Begin Interpret \"%s\" ..\n",argv[1]);
	read_file(argv[1], buffer);
	//printf("%s",buffer);
	token* anchor = tokenize(buffer);
	///print_tokens(anchor);
	// printf("\n");
	///int num_tokens = count_tokens(anchor);
	///printf("NUM TOKENS: %d\n", num_tokens);

	/*printf("\n");
	
	treenode* treenode_anchor = build_parser_tree(anchor);
	
	printf("\n");

	//print_tree(treenode_anchor, 0);
	//print_children(treenode_anchor);
	print_tree(treenode_anchor, 0);*/
	
	//parser_test(anchor);
	
	treenode* treenode_anchor = build_parse_tree(anchor);
	free_tokens(anchor); // Free up all tokens
	printf("\n");
	print_tree(treenode_anchor,0);
	
	printf(".. Finished Interpreting \"%s\" ..\n",argv[1]);
	return 0;
}