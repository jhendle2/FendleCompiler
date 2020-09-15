#ifndef TOKENIZER
#define TOKENIZER

#define WORD_SIZE 32
#define BUFFER_SIZE 255

typedef struct token{
	struct token* next;
	char word[WORD_SIZE];
} token;

token* new_token(char word[WORD_SIZE]);
void read_file(char FILENAME[WORD_SIZE], char buffer[BUFFER_SIZE]);
int is_whitespace(char c);
int is_comment(char c);
int is_delimiter(char c);
void print_tokens(token* anchor);
void sanitize_string(char str[WORD_SIZE]);
token* tokenize(char buff[BUFFER_SIZE]);
int count_tokens(token* anchor);

#endif