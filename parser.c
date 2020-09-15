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

treenode* new_treenode_full(char word[WORD_SIZE], enum TYPE type, int size, int constant_value, int max_num_children){
	treenode* out = (treenode*)malloc(sizeof(treenode));
	strncpy(out->word,word,WORD_SIZE);
	out->type = type;
	out->size = size;
	out->constant_value = constant_value;
	out->last_child_index = 0;
	
	out->max_num_children = max_num_children;
	out->children = (treenode**)malloc(sizeof(treenode*)*max_num_children); // sizeof(treenode*) or sizeof(treenode) ?? This fixes segfault error
	// printf("!! NTF: SIZE = %d\n",(int)(sizeof(out->children)));
		
	return out;
}

treenode* new_treenode_minimal(char word[WORD_SIZE], enum TYPE type){
	return new_treenode_full(word,type,0,0,MAX_CHILDREN_SIZE);
}

treenode* new_treenode_simple(char word[WORD_SIZE]){
	return new_treenode_full(word,TYPE_NONE,0,0,MAX_CHILDREN_SIZE);	
}

void treenode_add_child(treenode* parent, treenode* child){
	int child_index = parent->last_child_index;
	if(child_index == parent->max_num_children - 1) return;
	
	parent->children[child_index] = child;
	parent->last_child_index++;
	parent->num_children++;
	// printf("\tAdded child: <%s> @ %d\n",child->word,child_index);
}

void print_treenode(treenode* node){
	if(node==NULL){ // Prevents segfault for null nodes
		printf("<NONEXISTENT NODE>\n");
		return;
	}
	
	//printf("!PRINT_TREENODE\n");
	
	char word[WORD_SIZE];
	strncpy(word,node->word,WORD_SIZE);
		
	enum TYPE type = node->type;
	
	char typestr[WORD_SIZE];
	strncpy(typestr,type2str(type),strlen(type2str(type)));
	
	int size = node->size;
	int val = node->constant_value;
	
	printf("<%s> : type=%s, size=%d, val=%d\n",
		word, typestr, size, val);
}

void print_tree(treenode* anchor){
	//printf("!PRINT_TREE\n");
	
	treenode* temp_treenode = anchor;
	
	if(temp_treenode->num_children == 0){ // Just print self
		print_treenode(temp_treenode);
	}
	
	else{ // Print self then children
		int num_children = temp_treenode->num_children;
		treenode** children = temp_treenode->children;

		print_treenode(temp_treenode);
		for(int i = 0; i<num_children; i++){
			printf("\t");
			print_tree(children[i]);
		}
		printf("\n");
	}
}

treenode* build_parser_tree(token* token_anchor){
	treenode* anchor = new_treenode_simple("TREENODE_ANCHOR");
	token* token_temp = token_anchor;
	
	while(token_temp != NULL){
		printf("@ token: %s\n", token_temp->word);
		treenode* child_treenode = new_treenode_simple(token_temp->word);
		treenode_add_child(anchor, child_treenode);
		
		token_temp = token_temp->next;
	}
	
	return anchor;
}