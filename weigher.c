#include <stdio.h>
#include <stdlib.h>

#include "weigher.h"

int type2weight(enum TYPE type){
	switch(type){
		case TYPE_METHOD:
			return 0;
		case TYPE_BRANCH:
			return 0;
		case TYPE_IF:
			return 0;
		case TYPE_ELSE:
			return 0;
	
		case TYPE_VARIABLE:
			return 0;
		case TYPE_VARIABLE_INT:
			return 0;
		case TYPE_VARIABLE_CHAR:
			return 0;
	
		case TYPE_CONSTANT:
			return 1;
			
		case TYPE_NONE:
		default:
			break;
	}
	return "NONE";	
}

int get_weight(enum TYPE type, int level){
	
}