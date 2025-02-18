#pragma once
#include <stdlib.h>

typedef struct char_stack {

	char* char_array;
	int*  size_array;
	int   cur_member;
	int   member_cnt;
	int   used_char ;
	int   free_char ;

} char_stack_st;


void  create_stack  (char_stack_st* src, int init_size, int member_cnt);

void  destroy_stack (char_stack_st* src);

void grow_stack (char_stack_st* src, int incr);

void grow_member_cnt (char_stack_st* src);

void  put_item (char_stack_st* src, char* item, int size);

int  get_item (char_stack_st* src, char* buffer);

