#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "breakers.h"

#define MAX_SIZE 40
#define MAX_URL  21
#define MAX_NUM  100

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

	if(res > 100)
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

int main() {
	
	int i = 0, shift = 0;

	char* history = NULL;
	history = calloc(MAX_URL * 4, sizeof(char));
	func_breaker(history != NULL)
	int history_size = MAX_URL * 4;

	list_head_st browser_list;
	init_list (&browser_list);

	list_member_st* tmp = NULL;	

	char* input_str = NULL;
	input_str = calloc(MAX_SIZE, sizeof(char));
	func_breaker(input_str != NULL)

	command_st cur_com;
	cur_com.arg_size = 1;
	cur_com.arg_num  = 0;	

	cur_com.arg_str = calloc(MAX_URL, sizeof(char));
	func_breaker(cur_com.arg_str != NULL)
	cur_com.arg_str[0] = '\0';

	{ //creating homepage
		char string[9] = "homepage";
	
		insert_member (&browser_list, browser_list.list_size + 1, string, 9);
				
		for(int j = i * MAX_URL, k = 0; k < 9; ++j, ++k)
			history[j] = string[k];

		++i;
	}

	do {
		func_breaker(input_str == fgets(input_str, MAX_SIZE, stdin))
		get_command (&cur_com, input_str, MAX_SIZE);

		//printf("Command %d: opcode - %d, arg_num - %d, arg_size - %d, arg_str - %s\n", i, cur_com.opcode, cur_com.arg_num, cur_com.arg_size, cur_com.arg_str);

		switch(cur_com.opcode) {
			case NOP    :
				break;

			case VISIT  :
				if(shift > 0)
					while(shift > 0) {
						delete_member (&browser_list, browser_list.list_size);
						--shift;
					}

				shift = 0;
				insert_member (&browser_list, browser_list.list_size + 1, cur_com.arg_str, cur_com.arg_size);
				
				if((history_size - (i * MAX_URL)) < MAX_URL)
					history_size = grow_history(&history, history_size);

				for(int j = i * MAX_URL, k = 0; k < cur_com.arg_size; ++j, ++k)
					history[j] = cur_com.arg_str[k];

				++i;

				break;

			case BACK   :
				if(cur_com.arg_num > (browser_list.list_size - shift))
					shift = browser_list.list_size - 1;
				
				else
					shift = cur_com.arg_num;

				tmp = goto_member (&browser_list, browser_list.list_size - shift);
				func_breaker(tmp != NULL)
				
				if((history_size - (i * MAX_URL)) < MAX_URL)
					history_size = grow_history(&history, history_size);

				for(int j = i * MAX_URL, k = 0; k < tmp->size; ++j, ++k)
					history[j] = tmp->str[k];

				++i;

				break;

			case FORWARD:
				if(cur_com.arg_num > shift)
					shift = 0;
				
				else
					shift -= cur_com.arg_num;

				tmp = goto_member (&browser_list, browser_list.list_size - shift);
				func_breaker(tmp != NULL)
				
				if((history_size - (i * MAX_URL)) < MAX_URL)
					history_size = grow_history(&history, history_size);

				for(int j = i * MAX_URL, k = 0; k < tmp->size; ++j, ++k)
					history[j] = tmp->str[k];

				++i;

				break;

			default:
				break;

		}


	} while(input_str[0] != '\n');


	printf("Browser history: \n");
	for(int j = 0; j < i; ++j)
		printf("%s\n", &(history[j * MAX_URL]));

	free(history        );
	free(input_str      );
	free(cur_com.arg_str);


	return 0;

}
