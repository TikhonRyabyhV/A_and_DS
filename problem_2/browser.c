#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "breakers.h"

#define MAX_SIZE 40
#define MAX_URL  21

#define NOP     0
#define VISIT   1
#define BACK    2
#define FORWARD 3

typedef struct command {

	char* arg_str ;
	int   arg_size;
	int   arg_num ;
	int   opcode  ;

} command_st;

int comp_str (char* a, char* b, int size) {
	
	func_breaker(size > 0)

	func_breaker(a != NULL)
	func_breaker(b != NULL)

	for(int i = 0; i < size; ++i)
		if(a[i] != b[i])
			return 0;

	return 1;

}

int get_num (char* src, int max_num) {

	void_func_breaker(src != NULL)

	int i = 0, j = 0, res = 0;

	while(!('1' <= src[i] && src[i] <= '9'))
		++i;

	char buffer[4];

	while(('1' <= src[i] && src[i] <= '9') && j < 3) {
		buffer[j] = src[i];
		++i;
		++j;
	}

	buffer[j] = '\0';

	res = atoi(buffer);

	if(res > 100)
		return 0  ;
	else
		return res;

}

int get_URL (char* src, char* dst, int dst_size) {
	
	void_func_breaker(src != NULL)
	void_func_breaker(dst != NULL)

	void_func_breaker(dst_size > 0)

	int i = 0;

	while((i < dst_size - 1) && !(('a' <= src[i] && src[i] <= 'z') || ('A' <= src[i] && src[i] <= 'Z') || ('1' <= src[i] && src[i] <= '9') || src[i] == '.'))
		++i;


	while((i < dst_size - 1) && (('a' <= src[i] && src[i] <= 'z') || ('A' <= src[i] && src[i] <= 'Z') || ('1' <= src[i] && src[i] <= '9') || src[i] == '.')) {
		dst[i] = src[i];
		++i;
	}

	dst[i] = '\0';

	return i + 1;

}

void get_command (command_st* dst, char* src, int size) {
		
	void_func_breaker(dst != NULL)
	void_func_breaker(src != NULL)
	
	void_func_breaker(size > 0 && size <= MAX_SIZE)

	char buffer[MAX_SIZE];
	fscanf(src, "%s", buffer);

	if(comp_str(buffer, "visit", 6)) {
		dst->opcode  = VISIT;
		dst->arg_num = 0    ;

		dst->arg_size = get_URL (buffer, dst->arg_str, MAX_URL);
	}

	else {
		if(comp_str(buffer, "back", 5)) {
			dst->opcode   = BACK;
			dst->arg_size = 1   ;
			cur_com.arg_str[0] = '\0';

			dst->arg_num = get_num (buffer, MAX_NUM);
		}
			
		else {
			if(comp_str(buffer, "forward", 8)) {
				dst->opcode   = FORWARD;
				dst->arg_size = 1   ;
				cur_com.arg_str[0] = '\0';

				dst->arg_num = get_num (buffer, MAX_NUM);
			}

			else {
				dst->opcode   = NOP;
				dst->arg_size = 1  ;
				cur_com.arg_str[0] = '\0';
				dst->arg_num  = 0  ;
			}
		}

	}

	return;

}

int main() {
	
	char* input_str = NULL;
	input_str = calloc(MAX_SIZE, sizeof(char));
	func_breaker(input_str != NULL)

	command_st cur_com;
	cur_com.arg_size = 1;
	cur_com.arg_num  = 0;	

	cur_com.arg_str = calloc(MAX_URL, sizeof(char));
	func_breaker(cur_com.arg_str != NULL)
	cur_com.arg_str[0] = '\0';

	do {
		func_breaker(input_str == fgets(input_str, MAX_SIZE, stdin))
		get_command (&cur_com, input_str, MAX_SIZE);

		printf("Command %d: opcode - %d, arg_num - %d, arg_size - %d, arg_str - %s\n", i, cur_com.opcode, cur_com.arg_num, cur_com.arg_size, cur_com.arg_str);


	} while(input_string[0] != '\n');

	free(cur_com.arg_str);


	return 0;

}
