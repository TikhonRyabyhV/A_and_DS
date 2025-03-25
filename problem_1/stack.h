#pragma once
#include <stdlib.h>

typedef struct char_stack {

	char* char_array; //pointer for array of chars
	int*  size_array; //array of items' sizes
	int   cur_member; //number of last item in stack
	int   member_cnt; //number of all members in stack
	int   used_char ; //chars of array that are used for items
	int   free_char ; //chars of array that are not used for items

} char_stack_st;


void  create_stack  (char_stack_st* src, int init_size, int member_cnt); //stack initialization

void  destroy_stack (char_stack_st* src);

void grow_stack (char_stack_st* src, int incr); //increase char array size

void grow_member_cnt (char_stack_st* src); //increase number of all elements of stack

void  put_item (char_stack_st* src, char* item, int size); //add some new item

int  get_item (char_stack_st* src, char* buffer); //get last item, it will be put in buffer

