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

	char* input_string[4] = {
		"/home////////////////////////Downloads///////",
		"/home/./Downloads/Films/../Stories/"          ,
		"/home/base/../../../"                         ,
		"/home/Downloads/../Files/./GitHub////../"     
	};
	char* expectation[4] = {
		"/home/Downloads"                                     ,
		"/home/Downloads/Stories"                             ,
		"Going upper than the root directory is not possible.",
		"/home/Files"     
			
	};

	char* output_string[4];
	for(int i = 0; i < 4; ++i) {
		output_string[i] = calloc(PATH_MAX, sizeof(char));
		func_breaker(output_string[i] != NULL)
	}
	
	char* buffer;
	buffer = calloc(PATH_MAX, sizeof(char));
	func_breaker(buffer != NULL)


	char* sp_str[2] = {".", ".."};

	for(int i = 0; i < 4; ++i) {

		int result   = 0;
		int res_size = 0;
		
		int cur_char      = 0;
		int dir_size      = 0;
		int path_size     = 1;
		int prev_dir_size = 0;
		int flag          = 0; //indicates . and ..

		char* dir_ptr = NULL;

		while(input_string[i][cur_char] != '\0') {

			cur_char = skip_slashes(input_string[i], cur_char);

			dir_ptr = &(input_string[i][cur_char]);
			if(input_string[i][cur_char] == '\0')
				break;

			dir_size = cur_char;

			cur_char = get_dir(input_string[i], cur_char);

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
				if(path_size == 1) {
					char* error = "Going upper than the root directory is not possible.";

					res_size = 0;
					while(error[res_size] != '\0') {
						output_string[i][res_size] = error[res_size];
						++res_size;
					}
					output_string[i][res_size] = '\0';

					goto label;
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


		if(path_size == 1) {
			output_string[i][0] = '/' ;
			output_string[i][1] = '\0';

			res_size = 1;
		}

		else {
			output_string[i][path_size] = '\0';
			
			--path_size;
			res_size = path_size;
		}

		while(path_size > 0) {

			item_size = get_item(&stack, buffer);

			for(int j = path_size - item_size, k = 0; j < path_size, k < item_size; ++j, ++k)
				output_string[i][j] = buffer[k];

			output_string[i][path_size - item_size - 1] = '/';

			path_size -= (item_size + 1);

		}

		label:

		result = comp_str (output_string[i], expectation[i], res_size);

		printf("\nTest #%d:\n", i + 1);
		printf("Input  string: %s\n", input_string [i]);
		printf("Output string: %s\n", output_string[i]);
		printf("Expectation  : %s\n", expectation  [i]);
		
		printf("Result: %d\n", result);
		printf("------------------------------------------------------------");



	}

	destroy_stack(&stack);

	free(buffer      );

	for(int i = 0; i < 4; ++i)
		free(output_string[i]);

	return 0;

}
