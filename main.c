#include <stdio.h>
#include "stack.h"

int main() {
	char_stack_st my_stack;
	
	create_stack(&my_stack, 5, 2);

	char* strings[4] = {"hell", "asd", "po", "l"};
	char  buffer[5];

	put_item(&my_stack, strings[0], 5);
	printf("Stack size: %d\n", my_stack.member_cnt);

	put_item(&my_stack, strings[3], 5);
	printf("Stack size: %d\n", my_stack.member_cnt);

	get_item(&my_stack, buffer);
	printf("%s\n", buffer);

	put_item(&my_stack, strings[2], 5);
	printf("Stack size: %d\n", my_stack.member_cnt);

	put_item(&my_stack, strings[1], 5);
	printf("Stack size: %d\n", my_stack.member_cnt);
	
	get_item(&my_stack, buffer);
	printf("%s\n", buffer);

	get_item(&my_stack, buffer);
	printf("%s\n", buffer);

	get_item(&my_stack, buffer);
	printf("%s\n", buffer);

	destroy_stack(&my_stack);

	
	return 0;
}
