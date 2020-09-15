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
		while ((c = getc(file)) != EOF){
			//putchar(c);
			iterator++;
			sprintf(buffer,"%s%c",buffer,c);
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
			sprintf(temp_str,"%c",c);
			for(j = i+1; j<BUFFER_SIZE; j++){
				char k = buff[j];
				sprintf(temp_str,"%s%c",temp_str,k);
				if(k == '\'' || k == '\"') break;
			}
			i = j+1;
			
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
				// strcpy(temp_str,"");
			}
			
			sanitize_string(temp_str);
		}
		
		else if( is_delimiter(c) ){
			if(strlen(temp_str)>0){
				token* new_temp_token = new_token(temp_str);
				temp_anchor->next = new_temp_token;
				temp_anchor = temp_anchor->next;
			
				sanitize_string(temp_str);
				//strcpy(temp_str,"");
			}
			
			//printf("TEMP: %s\n",temp_str);
			sprintf(temp_str,"%c",c);
			token* new_delim_token = new_token(temp_str);
			temp_anchor->next = new_delim_token;
			temp_anchor = temp_anchor->next;
			
			sanitize_string(temp_str);
		}
		
		else{
			sprintf(temp_str,"%s%c",temp_str,c);
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
	if(anchor==NULL) return 0;
	return 1+count_tokens(anchor->next);
}