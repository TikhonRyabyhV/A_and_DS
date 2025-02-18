#include <stdlib.h>
#include "browser_funcs.h"
#include "breakers.h"

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

	func_breaker(src != NULL)

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

	if(res > max_num)
		return 0  ;
	else
		return res;

}

int get_URL (char* src, char* dst, int dst_size) {
	
	func_breaker(src != NULL)
	func_breaker(dst != NULL)

	func_breaker(dst_size > 0)

	int i = 0, j = 0;

	while(!(('a' <= src[i] && src[i] <= 'z') || ('A' <= src[i] && src[i] <= 'Z') || ('1' <= src[i] && src[i] <= '9') || src[i] == '.'))
		++i;


	while((j < dst_size - 1) && (('a' <= src[i] && src[i] <= 'z') || ('A' <= src[i] && src[i] <= 'Z') || ('1' <= src[i] && src[i] <= '9') || src[i] == '.')) {
		dst[j] = src[i];
		++i;
		++j;
	}

	dst[j] = '\0';

	return j + 1;

}

void get_command (command_st* dst, char* src, int size) {
		
	void_func_breaker(dst != NULL)
	void_func_breaker(src != NULL)
	
	void_func_breaker(size > 0 && size <= MAX_SIZE)

	char buffer[MAX_SIZE];
	int i = 0, j = 0;

	while(src[i] == ' ')
		++i;


	while((j < MAX_SIZE - 1) && src[i] != ' ' && src[i] != '\0' && src[i] != '\n') {
		buffer[j] = src[i];
		++i;
		++j;
	}

	buffer[j] = '\0';

	if(comp_str(buffer, "visit", 6)) {
		dst->opcode  = VISIT;
		dst->arg_num = 0    ;

		dst->arg_size = get_URL (src + i, dst->arg_str, MAX_URL);
	}

	else {
		if(comp_str(buffer, "back", 5)) {
			dst->opcode     = BACK;
			dst->arg_size   = 1   ;
			dst->arg_str[0] = '\0';

			dst->arg_num = get_num (src + i, MAX_NUM);
		}
			
		else {
			if(comp_str(buffer, "forward", 8)) {
				dst->opcode     = FORWARD;
				dst->arg_size   = 1      ;
				dst->arg_str[0] = '\0'   ;

				dst->arg_num = get_num (src + i, MAX_NUM);
			}

			else {
				dst->opcode     = NOP ;
				dst->arg_size   = 1   ;
				dst->arg_str[0] = '\0';
				dst->arg_num    = 0   ;
			}
		}

	}

	return;

}

int grow_history (char** src, int size) {
	
	func_breaker(src    != NULL)
	func_breaker((*src) != NULL)

	func_breaker(size > 0)

	(*src) = realloc ((*src), (size * 2) * sizeof(char));
	func_breaker((*src) != NULL)

	return size * 2;

}

