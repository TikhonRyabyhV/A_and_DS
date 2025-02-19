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

#ifdef TEST
	char* input_data[4] = {
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

	int test_num = 0, success = 0, result = 0;
#endif

	char* input_string = NULL;
#ifndef TEST
	input_string = calloc(PATH_MAX, sizeof(char));
	func_breaker(input_string != NULL)
#endif
	
	char* output_string = NULL;
	output_string = calloc(PATH_MAX, sizeof(char));
	func_breaker(output_string != NULL)


	char* buffer;
	buffer = calloc(PATH_MAX, sizeof(char));
	func_breaker(buffer != NULL)

	char* sp_str[2] = {".", ".."};

#ifndef TEST
	func_breaker(input_string == fgets(input_string, PATH_MAX, stdin))
	
	int k = 0;
	while(input_string[k] != '\n')
		++k;
	input_string[k] = '\0';
#else
test_label:
	input_string = input_data[test_num];

	result = 0;
#endif
	
	int cur_char      = 0;
	int dir_size      = 0;
	int path_size     = 0;
	int prev_dir_size = 0;
	int flag          = 0; //indicates . and ..

	char* dir_ptr = NULL;

	while(input_string[cur_char] != '\0') {

		cur_char = skip_slashes(input_string, cur_char);

		dir_ptr = &(input_string[cur_char]);
		if(input_string[cur_char] == '\0')
			break;

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
				
			#ifndef TEST
				printf("Going upper than the root directory is not possible.");

				destroy_stack(&stack);

				free(input_string );
				free(output_string);
				free(buffer       );

				return 0;
			#else
				char* error = "Going upper than the root directory is not possible.";

				while(error[path_size] != '\0') {
					output_string[path_size] = error[path_size];
					++path_size;
				}
				output_string[path_size] = '\0';

				goto err_label;
			#endif
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
	
	if(path_size == 0) {
		output_string[0] = '/';
		output_string[1] = '\0';
	}
	
	else
		output_string[path_size] = '\0';

	while(path_size > 0) {

		item_size = get_item(&stack, buffer);

		for(int i = path_size - item_size, j = 0; i < path_size, j < item_size; ++i, ++j)
			output_string[i] = buffer[j];

		output_string[path_size - item_size - 1] = '/';

		path_size -= (item_size + 1);

	}

#ifdef TEST
err_label:
		result = comp_str (output_string, expectation[test_num], 1);

		printf("\n------------------------------------------------------------\n");	
		printf("Test #%d\n", test_num + 1);
		printf("Input  string: %s\n", input_data [test_num]);
		printf("Output string: %s\n", output_string         );
		printf("Expectation  : %s\n", expectation[test_num]);
		
		printf("Result: %d", result);
		printf("\n------------------------------------------------------------\n");	

		++test_num;

		success += result;

		if(test_num < 4)
			goto test_label;
		else
			printf("Summary: %d/4 tests were completed\n", success);
#else
	printf("%s", output_string);
#endif

	destroy_stack (&stack);

	free (buffer       );
	free (output_string);

#ifndef TEST
	free(input_string);
#endif

	return 0;

}
