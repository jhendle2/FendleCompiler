#ifndef TOKENIZER
#define TOKENIZER

typedef struct token{
	struct token* next;
	char word[32];
} token;

token* new_token(char word[32]);
void read_file(char FILENAME[32], char buffer[255]);
int is_whitespace(char c);
int is_comment(char c);
int is_delimiter(char c);
void print_tokens(token* anchor);
void sanitize_string(char str[32]);
token* tokenize(char buff[255]);

#endif