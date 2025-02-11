#pragma once
#include <stdlib.h>

typedef struct char_stack {

	char* first_member;
	int   cur_member  ;
	int   member_len  ;
	int   member_cnt  ;

} char_stack_st;


void  create_stack  (char_stack_st* src, int mem_len, int mem_cnt);

void  destroy_stack (char_stack_st* src);

void grow_stack (char_stack_st* src);

void  put_item (char_stack_st* src, char* item, int size);

void  get_item (char_stack_st* src, char* buffer);
