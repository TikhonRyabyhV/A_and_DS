#include <stdio.h>
#include "stack.h"

int main() {
	char_stack_st my_stack;
	
	create_stack(&my_stack, 1, 1);

	char* strings[4] = {"hell", "asd--------------------", "p^7o", "l"};
	char  buffer[100];

	put_item(&my_stack, strings[0], 5);
	printf("Stack size: %d, chars size: %d, cur_member: %d\n", my_stack.member_cnt, my_stack.used_char + my_stack.free_char, my_stack.cur_member);

	put_item(&my_stack, strings[3], 2);
	printf("Stack size: %d, chars size: %d, cur_member: %d\n", my_stack.member_cnt, my_stack.used_char + my_stack.free_char, my_stack.cur_member);

	get_item(&my_stack, buffer);
	printf("%s\n", buffer);

	put_item(&my_stack, strings[2], 5);
	printf("Stack size: %d, chars size: %d, cur_member: %d\n", my_stack.member_cnt, my_stack.used_char + my_stack.free_char, my_stack.cur_member);

	put_item(&my_stack, strings[1], 24);
	printf("Stack size: %d, chars size: %d, cur_member: %d\n", my_stack.member_cnt, my_stack.used_char + my_stack.free_char, my_stack.cur_member);
	
	get_item(&my_stack, buffer);
	printf("%s\n", buffer);

	get_item(&my_stack, buffer);
	printf("%s\n", buffer);

	get_item(&my_stack, buffer);
	printf("%s\n", buffer);

	destroy_stack(&my_stack);

	
	return 0;
}
