#ifndef PARSER
#define PARSER

#include "tokenizer.h"
#include "weigher.h"

#define MAX_CHILDREN_SIZE 8

enum TYPE{
	TYPE_NONE,
	
	TYPE_BRANCH,
	TYPE_IF,
	TYPE_ELSE,
	
	TYPE_VARIABLE,
	TYPE_VARIABLE_INT,
	TYPE_VARIABLE_CHAR,
	
	TYPE_CONSTANT
};

typedef struct treenode{
	char word[WORD_SIZE];
	struct treenode** children;
	
	int max_num_children;
	int num_children;
	int last_child_index;
	
	enum TYPE type;
	int size;
	int constant_value;
} treenode;

char* type2str(enum TYPE type);

treenode* new_treenode_full(char word[WORD_SIZE], enum TYPE type,
	int size, int constant_value, int max_num_children);
treenode* new_treenode_minimal(char word[WORD_SIZE], enum TYPE type);
treenode* new_treenode_simple(char word[WORD_SIZE]);

void print_treenode(treenode* node);
void print_tree(treenode* anchor);
treenode* build_parser_tree(token* token_anchor);

#endif