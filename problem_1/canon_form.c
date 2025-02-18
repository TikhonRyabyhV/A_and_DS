#include <stdio.h>
#include <stdlib.h>

#include "breakers.h"
#include "stack.h"

#define PATH_MAX 4096

int comp_str (char* a, char* b, int size) {
	
	func_breaker(size > 0)

	func_breaker(a != NULL)
	func_breaker(b != NULL)

	for(int i = 0; i < size; ++i)
		if(a[i] != b[i])
			return 0;

	return 1;

}

int skip_slashes (char* src, int start) {
	
	func_breaker(src != NULL)
	func_breaker(start >= 0 )

	int i = start;

	while(src[i] == '/')
		++i;

	return i;

}

int get_dir(char* src, int start) {

	func_breaker(src      != NULL)

	func_breaker(start >= 0 )

	int i = start;

	while(src[i] != '/' && src[i] != '\0') 
		++i;

	return i;

}

int main() {

	char_stack_st stack;
	create_stack(&stack, 1, 1);

	char* input_string;
	input_string = calloc(PATH_MAX, sizeof(char));
	func_breaker(input_string != NULL)
	
	char* buffer;
	buffer = calloc(PATH_MAX, sizeof(char));
	func_breaker(buffer != NULL)

	func_breaker(input_string == fgets(input_string, PATH_MAX, stdin))


	char* sp_str[2] = {".", ".."};

	int cur_char      = 0;
	int dir_size      = 0;
	int path_size     = 0;
	int prev_dir_size = 0;
	int flag          = 0; //indicates . and ..

	char* dir_ptr = NULL;

	while(input_string[cur_char] != '\0') {

		cur_char = skip_slashes(input_string, cur_char);

		dir_ptr = &(input_string[cur_char]);
		func_breaker(input_string[cur_char] != '\0')

		dir_size = cur_char;

		cur_char = get_dir(input_string, cur_char);

		dir_size = cur_char - dir_size;

		switch(dir_size) {
			case 1:
				flag =     comp_str(dir_ptr, sp_str[0], 1);
				break;
			case 2:
				flag = 2 * comp_str(dir_ptr, sp_str[1], 2);
				break;
			default:
				break;
		}


		if(flag == 2) {
			if(path_size == 0) {
				printf("Going upper than the root directory is not possible.\n");

				destroy_stack(&stack);

				free(input_string);
				free(buffer      );

				return 0;
			}	

			prev_dir_size = get_item(&stack, buffer);

			path_size -= (prev_dir_size + 1);
		}

		else {

			if(flag == 1);

			else {
				put_item(&stack, dir_ptr, dir_size);
			
				path_size += (dir_size + 1); 
			}
		}

		dir_ptr  = NULL;
		dir_size = 0   ;
		flag     = 0   ;
	
	
	}

	int item_size = 0;
	
	input_string[path_size] = '\0';

	while(path_size > 0) {

		item_size = get_item(&stack, buffer);

		for(int i = path_size - item_size, j = 0; i < path_size, j < item_size; ++i, ++j)
			input_string[i] = buffer[j];

		input_string[path_size - item_size - 1] = '/';

		path_size -= (item_size + 1);

	}

	printf("Canon form of the path: \n");
	printf("%s\n", input_string);

	destroy_stack(&stack);

	free(input_string);
	free(buffer      );

	return 0;

}
