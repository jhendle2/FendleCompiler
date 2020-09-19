#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"


char* type2str(enum TYPE type){
	char* out = (char*)malloc(sizeof(char)*32);
	sanitize_string(out);
	
	switch(type){
		case TYPE_METHOD:
			return "METHOD";
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
		case TYPE_STRING:
			return "STRING";
		case TYPE_OPERATOR:
			return "OPERATOR";
				
		case TYPE_NONE:
		default:
			break;
	}
	return "NONE";
}

enum TYPE str2type(char type_as_word[WORD_SIZE]){
	if		(strcmp(type_as_word,"function")==0) return TYPE_METHOD;
	else if (strcmp(type_as_word,"if")==0)		return TYPE_IF;
	else if	(strcmp(type_as_word,"else")==0) 	return TYPE_ELSE;
	else if (strcmp(type_as_word,"var")==0)		return TYPE_VARIABLE;
	else if	(strcmp(type_as_word,"print")==0) 	return TYPE_METHOD;
	else if (word_is_string(type_as_word)) return TYPE_STRING;
	else if (is_delimiter(type_as_word[0])) return TYPE_OPERATOR;
	
	// Add more as you see fit
	
	return TYPE_NONE;
}

int find_constant_from_word(char word[WORD_SIZE]){
	if(word_is_number(word)){
		return atoi(word);
	}
	/*else{ // This will never happen?
		printf("[SYNTAX ERROR]: TRYING TO ASSIGN NON-CONSTANT VALUE TO CONSTANT\n");
		exit(1);
	}*/
	return 0;
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
	
	return out;
}

treenode* new_treenode_simple(char word[WORD_SIZE]){
	return new_treenode_full(word,TYPE_NONE,0,0,MAX_CHILDREN_SIZE);	
}

treenode* token2treenode(token* t){
	enum TYPE type = str2type(t->word);
	
	int size = 0;
	int max_num_children = MAX_CHILDREN_SIZE;
	int constant_value = 0;
	if(word_is_number(t->word)) constant_value = find_constant_from_word(t->word);
	
	return new_treenode_full(t->word, type, size, constant_value, max_num_children);
}


void print_treenode(treenode* node){
	if(node==NULL){ // Prevents segfault for null nodes
		printf("<NONEXISTENT NODE>\n");
		return;
	}

	char word[WORD_SIZE];
	strncpy(word,node->word,WORD_SIZE);
		
	enum TYPE type = node->type;
	
	char typestr[WORD_SIZE];
	strcpy(typestr,type2str(type));
	
	///int size = node->size;
	///int val = node->constant_value;
	int num_children = node->num_children;
		
	///printf("<%s> : type=%s, parent=<%s>, #children=%d\n",word,typestr,node->parent->word,num_children);
	printf("<%s> : type=%s, #children=%d\n",word,typestr,num_children);
}

void treenode_add_child(treenode* parent, treenode* child){ // Add a child to treenode, increase children count
	int child_index = parent->last_child_index;
	if(child_index == parent->max_num_children - 1) return;
	
	parent->children[child_index] = child;
	parent->last_child_index++;
	parent->num_children++;
	printf("\t<%s> added child: <%s> @ %d\n",parent->word,child->word,child_index);
}

void print_tree(treenode* anchor, int level){ // Prints node and all children and their children and so on + proper tabbing
	print_treenode(anchor);
	if(anchor->num_children>0){
		int num_children = anchor->num_children;
		for(int i = 0; i<num_children; i++){
			for(int j = 0; j<level; j++) printf("\t");
			print_tree(anchor->children[i],1+level);
		}
	}
}

treenode* build_parse_tree(token* anchor){
	if(strcmp(anchor->word,"ANCHOR_TOKEN")!=0){
		printf("[PARSER ERROR]: No ANCHOR_TOKEN present.\n");
		exit(1);
	}
	
	token* temp = anchor->next;
	treenode* treenode_anchor = new_treenode_simple("TREENODE_ANCHOR");
	treenode* treenode_last = treenode_anchor; // Last node before current
	printf("!! Beginning node building on <%s>!!\n",treenode_last->word);
	
	while(temp!=NULL){
		treenode* treenode_temp = token2treenode(temp);
		treenode_temp->parent = treenode_last; // Set node parent to last biggest node

		if(treenode_temp->type==TYPE_METHOD){ // Begin adding children to method node
			treenode_add_child(treenode_last, treenode_temp); // Add new node as child to last big node
			treenode_last = treenode_temp; // This node is new biggest node
			printf("!! Entering Node <%s>!!\n",treenode_last->word);
		}
		else if(temp->word[0]=='}' || temp->word[0]==')'){ // Found close brace, leave this node (go back to parent)
			printf("!! Exiting Node <%s>!!\n",treenode_last->word);
			printf("!! Successfully added %d children !!\n",treenode_last->num_children);
			treenode_last = treenode_last->parent;
		}
		else{ // Add child to last treenode
			treenode* child = token2treenode(temp);
			child->parent = treenode_last;
			treenode_add_child(treenode_last,child);
		}
		
		temp = temp->next;
	}
	
	return treenode_anchor;
}