#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"

int main(){
	char buffer[255];
	read_file("testcode.txt", buffer);
	//printf("%s",buffer);
	token* anchor = tokenize(buffer);
	print_tokens(anchor);
	// printf("\n");
	int num_tokens = count_tokens(anchor);
	printf("NUM TOKENS: %d\n", num_tokens);
	
	///treenode* parser_tree = build_parser_tree(anchor);
	
	//printf("parser_tree child[0] = %s",parser_tree->children[0]->word);
	//print_treenode(parser_tree);
	//printf("\n");
	
	/*treenode* child_1 = parser_tree->children[0];
	treenode* child_2 = parser_tree->children[1];
	treenode* child_3 = parser_tree->children[2];
	treenode* child_4 = parser_tree->children[3];
	
	print_treenode(child_1);
	print_treenode(child_2);
	print_treenode(child_3);
	print_treenode(child_4);*/
	printf("\n");
	
	treenode* treenode_anchor = new_treenode_full("TREENODE_ANCHOR", TYPE_NONE, 0, 0, num_tokens);
	
	//treenode* treenode_anchor = new_treenode_simple("TREENODE_ANCHOR");
	build_parser_tree(treenode_anchor,anchor);
	
	printf("\n");
	///print_tree(parser_tree);
	print_tree(treenode_anchor, 0);
	
	//print_children(treenode_anchor);
	
	return 0;
}