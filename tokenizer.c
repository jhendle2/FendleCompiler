#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"

token* new_token(char word[WORD_SIZE]){ // Initializer for token based on word
	token* out = (token*)malloc(sizeof(token));
	strncpy(out->word,word,WORD_SIZE);
	return out;
}

void read_file(char FILENAME[WORD_SIZE], char buffer[BUFFER_SIZE]){ // Reads a file and puts output into char array buffer
	char c;
	FILE *file;
	int iterator = 0;
	file = fopen(FILENAME, "r");
	if(file) {
		while ((c = getc(file))){
			if(feof(file)) break; // EOF finder. Needed to Linux compatibility?
			iterator++;
			strncat(buffer, &c, 1); // Prevents memory error
		}
		fclose(file);
	}
	
	buffer[iterator] = 0; // Null character at end of buffer
}

char whitespace[WORD_SIZE] = " \t\n\r";
int is_whitespace(char c){ // Returns True for each whitespace, else False
	for(int i = 0; i<WORD_SIZE; i++){
		if(c == whitespace[i]) return i+1; // Always true for whitespace, even with index 0
	}
	return 0;
}

char comments[WORD_SIZE] = "#";
int is_comment(char c){ // Returns True for each comment char, else False
	for(int i = 0; i<WORD_SIZE; i++){
		if(c == comments[i]) return i+1; // Always true for comment chars, even with index 0
	}
	return 0;
}

char delimiters[WORD_SIZE] = "+-*/;=:()[]{}<>";
int is_delimiter(char c){ // Returns True for each delimiter, else False
	for(int i = 0; i<WORD_SIZE; i++){
		if(c == delimiters[i]) return i+1; // Always true for delimiters, even with index 0
	}
	return 0;
}

void print_tokens(token* anchor){ // Prints tokens starting from first non-anchor
	token* temp_token = anchor->next;
	int counter = 0;
	
	while(temp_token != NULL){
		printf("%d: <%s>\n",counter++,temp_token->word);
		temp_token = temp_token->next;
	}
}

void sanitize_string(char str[WORD_SIZE]){ // Fully empties a 32 length string
	for(int i = 0; i<WORD_SIZE; i++){
		str[i] = 0;
	}
}

token* tokenize(char buff[BUFFER_SIZE]){ // Breaks buffer at special chars into token array starting at anchor. Returns anchor
	token* anchor = new_token("ANCHOR_TOKEN");
	token* temp_anchor = anchor;
	char temp_str[WORD_SIZE];
	sanitize_string(temp_str);
	
	for(int i = 0; i<BUFFER_SIZE; i++){
		char c = buff[i];
		//printf("@ %c\n",c);
		if(c == 0) break; // Break when null character reached
		
		if( is_comment(c) ){
			int j; // New index
			for(j = i+1; j<BUFFER_SIZE; j++){
				char k = buff[j];
				if(k == '\n' || k == '\r' || k == 0) break;
			}
			i = j+1;
			
			sanitize_string(temp_str);
		}
		
		else if( c=='\'' || c=='\"'){
			int j; // New index
			strncat(temp_str, &c, 1);
			for(j = i+1; j<BUFFER_SIZE; j++){
				char k = buff[j];
				strncat(temp_str, &k, 1);
				if(k == '\'' || k == '\"') break;
			}
			i = j;
			
			token* new_temp_token = new_token(temp_str);
			temp_anchor->next = new_temp_token;
			temp_anchor = temp_anchor->next;
			
			sanitize_string(temp_str);
		}
		
		else if( is_whitespace(c) ){
			if(strlen(temp_str)>0){
				token* new_temp_token = new_token(temp_str);
				temp_anchor->next = new_temp_token;
				temp_anchor = temp_anchor->next;
			
				sanitize_string(temp_str);
			}
			
			sanitize_string(temp_str);
		}
		
		else if( is_delimiter(c) ){
			if(strlen(temp_str)>0){
				token* new_temp_token = new_token(temp_str);
				temp_anchor->next = new_temp_token;
				temp_anchor = temp_anchor->next;
			
				sanitize_string(temp_str);
			}
			
			strncat(temp_str, &c, 1);
			token* new_delim_token = new_token(temp_str);
			temp_anchor->next = new_delim_token;
			temp_anchor = temp_anchor->next;
			
			sanitize_string(temp_str);
		}
		
		else{
			strncat(temp_str, &c, 1);
		}
	}
			
	if(strlen(temp_str)>0){ // Add any string left in temp_str
		token* new_temp_token = new_token(temp_str);
		temp_anchor->next = new_temp_token;
		temp_anchor = temp_anchor->next;
	}
	
	return anchor;
}

int count_tokens(token* anchor){
	if(anchor==NULL) return -1;
	return 1+count_tokens(anchor->next);
}

int word_is_string(char word[WORD_SIZE]){
	return (strstr(word, "\"") != NULL);
}

char* const_values = "1234567890";

int word_is_number(char word[WORD_SIZE]){ // Only finds ints, no floats
	int is_number = 1;
	for(int i = 0; i<WORD_SIZE; i++){
		if(word[i] == 0) break;
		
		if(strchr(const_values,word[i]) == NULL) is_number *= 0; // If not digit, make false
	}
	return is_number;
}

int word_is_operator(char word[WORD_SIZE]){
	if(is_delimiter(word[0])) return 1;
	
	else if	(strcmp(word,"==")==0) return 1;
	
	return 0;
}

void free_tokens(token* anchor){
	token* t = anchor;
	int i = 0;
	while(t!=NULL){
		token* next = t->next;
		free(t);
		t = next;
		i++;
	}
	printf("<> Freed %d tokens\n",i);
}