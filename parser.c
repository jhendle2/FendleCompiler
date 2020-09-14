#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

char* type2str(enum TYPE type){
	switch(type){
		case TYPE_BRANCH:
			return "BRANCH";
		case TYPE_IF:
			return "IF";
		case TYPE_ELSE:
			return "ELSE";
	
		case TYPE_VARIABLE:
			return "VARIABLE";
		case TYPE_VARIABLE_INT:
			return "VARIABLE_INT";
		case TYPE_VARIABLE_CHAR:
			return "VARIABLE_CHAR";
	
		case TYPE_CONSTANT:
			return "CONSTANT";
			
		case TYPE_NONE:
		default:
			break;
	}
	return "NONE";
}

treenode* new_treenode_full(char word[32], enum TYPE type, int size, int constant_value){
	treenode* out = (treenode*)malloc(sizeof(treenode));
	strncpy(out->word,word,32);
	out->type = type;
	out->size = size;
	out->constant_value = constant_value;
	return out;
}

treenode* new_treenode_minimal(char word[32], enum TYPE type){
	return new_treenode_full(word,type,0,0);
}

treenode* new_treenode_simple(char word[32]){
	return new_treenode_full(word,TYPE_NONE,0,0);	
}

void treenode_add_child(treenode* parent, treenode* child){
	int child_index = parent->num_children;
	parent->children[child_index] = child;
	parent->num_children++;
}

void print_treenode(treenode* node){
	char word[32];
	strncpy(word,node->word,32);
		
	enum TYPE type = node->type;
	
	char typestr[32];
	strncpy(typestr,type2str(type),strlen(type2str(type)));
	
	int size = node->size;
	int val = node->constant_value;
	
	printf("<%s> : type=%s, size=%d, val=%d\n",
		word, typestr, size, val);
}

treenode* build_parser_tree(token* token_anchor){
	treenode* anchor = new_treenode_simple("TREENODE_ANCHOR");
	
	return anchor;
}