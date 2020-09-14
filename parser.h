#ifndef PARSER
#define PARSER

#include "tokenizer.h"

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
	char word[32];
	struct treenode** children;
	int num_children;
	
	enum TYPE type;
	int size;
	int constant_value;
} treenode;

char* type2str(enum TYPE type);

treenode* new_treenode_full(char word[32], enum TYPE type, int size, int constant_value);
treenode* new_treenode_minimal(char word[32], enum TYPE type);
treenode* new_treenode_simple(char word[32]);


#endif