#include <stdlib.h>
#include "list.h"
#include "browser_funcs.h"
#include "breakers.h"

int main() {
	

#ifdef TEST
	char* input_data[4][9] = {
		{"", "visit google.com", "back 2", "back 1", "forward 1", "\n", "", "", ""},
		{"", "visit google.com", "visit linux.org", "visit youtube.com", "back 1", "visit facebook.com", "back 1", "forward 1", "\n"},
		{"", "visit google.com", "visit mail.ru", "back 23", "forward 1", "visit vk.ru", "forward 1", "\n", ""},
		{"", "back 3", "visit mipt.ru", "forward 45", "visit google.com", "visit mail.ru", "back 1", "\n", "" }
	};

	char* expectation[4][8] = {
		{"homepage", "google.com", "homepage", "homepage", "google.com", "", "", ""},
		{"homepage", "google.com", "linux.org", "youtube.com", "linux.org", "facebook.com", "linux.org", "facebook.com"},
		{"homepage", "google.com", "mail.ru", "homepage", "google.com", "vk.ru", "vk.ru", ""},
		{"homepage", "homepage", "mipt.ru", "mipt.ru", "google.com", "mail.ru", "google.com", ""}
	};

	int test_num = 0, success = 0;
#endif
	int i = 0, shift = 0;

	char* history = NULL;
	history = calloc(MAX_URL * 4, sizeof(char));
	func_breaker(history != NULL)
	int history_size = MAX_URL * 4;

	list_head_st browser_list;
	init_list (&browser_list);

	list_member_st* tmp = NULL;	

	char* input_str = NULL;
#ifndef TEST
	input_str = calloc(MAX_SIZE, sizeof(char));
	func_breaker(input_str != NULL)
#endif

	command_st cur_com;
	cur_com.arg_size = 1;
	cur_com.arg_num  = 0;	

	cur_com.arg_str = calloc(MAX_URL, sizeof(char));
	func_breaker(cur_com.arg_str != NULL)
	cur_com.arg_str[0] = '\0';

#ifdef TEST
test_label:
	i     = 0;
	shift = 0;
#endif

	{ //creating homepage
		char string[9] = "homepage";
	
		insert_member (&browser_list, browser_list.list_size + 1, string, 9);
				
		for(int j = i * MAX_URL, k = 0; k < 9; ++j, ++k)
			history[j] = string[k];

		++i;
	}

	do {
	#ifndef TEST
		func_breaker(input_str == fgets(input_str, MAX_SIZE, stdin))
	#else
		input_str = input_data[test_num][i];
	#endif

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
				if(cur_com.arg_num >= (browser_list.list_size - shift))
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

	clear_list(&browser_list);

#ifndef TEST
	for(int j = 0; j < i; ++j)
		printf("%s\n", &(history[j * MAX_URL]));
#else
	int result = 1;
	for(int j = 0; j < i; ++j)
		result *= comp_str (&(history[j * MAX_URL]), expectation[test_num][j], 1); 

	if(result)
		++success;
	
	printf("\n-----------------------------------------------------\n");
	printf("\nTest #%d", test_num + 1);
	printf("\nInput: \n");
	int j = 1;
	while(input_data[test_num][j][0] != '\n') {
		printf("%s\n", input_data[test_num][j]);
		++j;
	}

	printf("\nOutput: \n");
	for(j = 0; j < i; ++j)
		printf("%s\n", &(history[j * MAX_URL]));

	printf("Result: %d\n", result);
	printf("\n-----------------------------------------------------\n");

	++test_num;

	if(test_num < 4)
		goto test_label;
	else
		printf("Summary: %d/4 tests was completed\n", success); 
#endif
	free(history        );
	free(cur_com.arg_str);

#ifndef TEST
	free(input_str);
#endif


	return 0;

}
