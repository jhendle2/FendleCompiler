#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct token{
	struct token* next;
	char word[32];
} token;

token* new_token(char word[32]){
	token* out = (token*)malloc(sizeof(token));
	strncpy(out->word,word,32);
	return out;
}

void read_file(char FILENAME[32], char buffer[255]){
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

char whitespace[32] = " \t\n\r";
int is_whitespace(char c){ // Returns True for each whitespace, else False
	for(int i = 0; i<32; i++){
		if(c == whitespace[i]) return i+1; // Always true for whitespace, even with index 0
	}
	return 0;
}

char comments[32] = "#";
int is_delimiter(char c){ // Returns True for each comment char, else False
	for(int i = 0; i<32; i++){
		if(c == comments[i]) return i+1; // Always true for comment chars, even with index 0
	}
	return 0;
}

char delimiters[32] = "+-*/;";
int is_delimiter(char c){ // Returns True for each delimiter, else False
	for(int i = 0; i<32; i++){
		if(c == delimiters[i]) return i+1; // Always true for delimiters, even with index 0
	}
	return 0;
}

void print_tokens(token* anchor){
	token* temp_token = anchor;
	int counter = 0;
	
	while(temp_token != NULL){
		printf("%d: <%s>\n",counter++,temp_token->word);
		temp_token = temp_token->next;
	}
}

void sanitize_string(char str[32]){
	for(int i = 0; i<32; i++){
		str[i] = 0;
	}
}

token* tokenize(char buff[255]){
	token* anchor = new_token("ANCHOR_TOKEN");
	token* temp_anchor = anchor;
	char temp_str[32];
	sanitize_string(temp_str);
	
	for(int i = 0; i<255; i++){
		char c = buff[i];
		if(c == 0) break; // Break when null character reached
		
		if( is_comment(c) ){
			int j = i+1; // New index
		}
		
		else if( is_whitespace(c) ){
			if(strlen(temp_str)>0){
				token* new_temp_token = new_token(temp_str);
				temp_anchor->next = new_temp_token;
				temp_anchor = temp_anchor->next;
			
				sanitize_string(temp_str);
				// strcpy(temp_str,"");
			}
		}
		
		else if( is_delimiter(c) ){
			if(strlen(temp_str)>0){
				token* new_temp_token = new_token(temp_str);
				temp_anchor->next = new_temp_token;
				temp_anchor = temp_anchor->next;
			
				sanitize_string(temp_str);
				//strcpy(temp_str,"");
			}
			
			token* new_delim_token = new_token(&c);
			temp_anchor->next = new_delim_token;
			temp_anchor = temp_anchor->next;
		}
		
		else{
			sprintf(temp_str,"%s%c",temp_str,c);
		}
	}
	
	return anchor;
}

int main(){
	char buffer[255];
	read_file("testcode.txt", buffer);
	//printf("%s",buffer);
	token* anchor = tokenize(buffer);
	print_tokens(anchor);
	return 0;
}