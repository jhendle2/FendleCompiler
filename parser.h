#ifndef PARSER2
#define PARSER2

#include "tokenizer.h"

#define MAX_CHILDREN_SIZE 32

enum TYPE{
	TYPE_NONE,
	
	TYPE_METHOD,
	
	TYPE_BRANCH,
	TYPE_IF,
	TYPE_ELSE,
	TYPE_ELSIF,
	
	TYPE_VARIABLE,
	TYPE_VARIABLE_INT,
	TYPE_VARIABLE_CHAR,
	
	TYPE_OPERATOR,
	TYPE_CONSTANT,
	TYPE_STRING
};

typedef struct treenode{
	char word[WORD_SIZE];
	struct treenode* parent;
	struct treenode** children;
	
	int max_num_children;
	int num_children;
	int last_child_index;
	
	enum TYPE type;
	int size;
	int constant_value;
} treenode;

char* type2str(enum TYPE type);
enum TYPE str2type(char word[WORD_SIZE]);

treenode* build_parse_tree(token* anchor);
void print_tree(treenode* tn, int level);
void parser_test(token* anchor);

#endif