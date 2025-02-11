#include "stack.h"

void create_stack (char_stack_st* src, int mem_len, int mem_cnt) {

		src->first_member = calloc(mem_cnt * mem_len, sizeof(char));

		if(src->first_member == NULL)
			return;

		src->cur_member = -1;
		src->member_len = mem_len;
		src->member_cnt = mem_cnt;

		return;
}

void destroy_stack (char_stack_st* src) {
	
	if(src->first_member == NULL)
		return;

	free(src->first_member);

	src->cur_member = -1;
	src->member_cnt = 0;

	return;
}

void grow_stack (char_stack_st* src) {
	
	src->first_member = realloc(src->first_member, src->member_len * src->member_cnt * 2 * sizeof(char));

	if(src->first_member == NULL)
		return;

	src->member_cnt *= 2;

	return;

}

void put_item (char_stack_st* src, char* item, int size) {
	
	if(((double) src->cur_member) / ((double) src->member_cnt) >= 0.8)
		grow_stack(src);

	src->cur_member++;

	char* start_ptr = &(src->first_member[src->cur_member * src->member_len]);

	for(int i = 0; i < src->member_len; i++)
		start_ptr[i] = item[i];

	return;
}

void get_item (char_stack_st* src, char* buffer) {
	
	char* start_ptr = &(src->first_member[src->cur_member * src->member_len]);

	for(int i = 0; i < src->member_len; i++)
		buffer[i] = start_ptr[i];

	src->cur_member--;

	return;

}

