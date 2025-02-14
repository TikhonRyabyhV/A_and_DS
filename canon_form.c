#include <stdio.h>
#include <stdlib.h>

#include "breakers.h"
#include "stack.h"

#define PATH_MAX 4096

int skip_slashes (char* src, int start) {
	
	void_func_breaker(src != NULL)
	void_func_breaker(start >= 0 )

	int i = start;

	while(src[i] == '/')
		++i;

	return i;

}

int get_dir(char* src, int start, int dir_size) {

	void_func_breaker(src != NULL)
	void_func_breaker(start >= 0 )

	int i = start;
	size = 0;

	while(src[i] != '/' || src[i] != '\0')
		++size;

	return i;

}

int main() {

	char_stack_st stack;
	create_stack(&stack, 1, 1);

	char* input_string;
	input_string = calloc(PATH_MAX, sizeof(char));
	void_func_breaker(input_string != NULL)
	
	char* buffer;
	buffer = calloc(PATH_MAX, sizeof(char));
	void_func_breaker(buffer != NULL)

	void_func_breaker(input_string == gets(input_string))

	int cur_char      = 0;
	int dir_size      = 0;
	int path_size     = 0;
	int prev_dir_size = 0;
	int flag          = 0; //indicates . and ..

	char* dir_ptr = NULL;

	while(input_string[cur_char] != '\0') {

		cur_char = skip_slashes(input_string, cur_char);

		dir_ptr = &(input_string[cur_char]);
		void_func_breaker(input_string[cur_char] != '\0')

		cur_char = get_dir(input_string, cur_char, dir_size);

		switch(dir_size) {
			case 1:
				flag =     comp_str(dir_ptr, sp_str[0], 1);
			case 2:
				flag = 2 * comp_str(dir_ptr, sp_str[1], 2);
			default:
				;
		}


		if(flag == 2) {
			if(path_size == 0) {
				printf();

				destroy_stack(&stack);

				free(input_string);
				free(buffer      );

				return 0;
			}	

			get_item(&stack, buffer);

			path_size -= (prev_dir_size + 1);
		}

		else {
			put_item(&stack, dir_ptr, dir_size);
			
			path_size += (dir_size + 1); 
		}

		prev_dir_size = dir_size;
		dir_ptr  = NULL;
		dir_size = 0   ;
	}

	for

	return 0;

}
