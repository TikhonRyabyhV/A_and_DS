#include "stack.h"
#include "breakers.h"

void create_stack (char_stack_st* src, int init_size, int member_cnt) {

		void_func_breaker(init_size  > 0)
		void_func_breaker(member_cnt > 0)

		src->char_array = calloc(init_size, sizeof(char));
		void_func_breaker(src->char_array != NULL)

		src->size_array = calloc(member_cnt, sizeof(int));
		void_func_breaker(src->size_array != NULL)

		src->cur_member = -1        ;
		src->member_cnt = member_cnt;
		src->used_char  = 0         ;
		src->free_char  = init_size ;

		return;
}

void destroy_stack (char_stack_st* src) {
	
	void_func_breaker(src != NULL)
	
	if(src->char_array == NULL)
		return;
	free(src->char_array);
	
	if(src->size_array == NULL)
		return;
	free(src->size_array);

	src->cur_member = -1;
	src->member_cnt = 0 ;
	src->used_char  = 0 ;
	src->free_char  = 0 ;

	return;
}

void grow_stack (char_stack_st* src, int incr) {

	void_func_breaker(src             != NULL)
	void_func_breaker(src->char_array != NULL)

	void_func_breaker(incr > 0)

	
	src->char_array = realloc(src->char_array, (src->used_char + src->free_char + incr) * sizeof(char));

	void_func_breaker(src->char_array != NULL)

	src->free_char = (src->used_char + src->free_char + incr) - src->used_char;

	return;

}


void grow_member_cnt (char_stack_st* src) {
	
	void_func_breaker(src             != NULL)
	void_func_breaker(src->size_array != NULL)

	src->size_array = realloc(src->size_array, src->member_cnt * 2 * sizeof(int));

	void_func_breaker(src->size_array != NULL)

	src->member_cnt *= 2;

	return;

}


void put_item (char_stack_st* src, char* item, int size) {
	
	void_func_breaker(src  != NULL)
	void_func_breaker(item != NULL)
	
	void_func_breaker(src->char_array != NULL)
	void_func_breaker(src->size_array != NULL)

	void_func_breaker(size > 0)

	if(((double) src->cur_member + 1) / ((double) src->member_cnt) >= 0.8)
		grow_member_cnt(src);
	
	if(((double) src->used_char) / ((double) src->used_char + src->free_char) >= 0.8)
		grow_stack(src, src->used_char + src->free_char);
	
	if(size > src->free_char)
		grow_stack(src, src->used_char + size);

	char* start_ptr = &(src->char_array[src->used_char]);

	for(int i = 0; i < size; i++)
		start_ptr[i] = item[i];
	
	src->cur_member++;
	src->size_array[src->cur_member] = size;

	src->used_char += size;
	src->free_char -= size;

	return;
}

void get_item (char_stack_st* src, char* buffer) {
	
	void_func_breaker(src    != NULL)
	void_func_breaker(buffer != NULL)
	
	void_func_breaker(src->char_array != NULL)
	void_func_breaker(src->size_array != NULL)

	int   item_size = src->size_array[src->cur_member];
	char* start_ptr = &(src->char_array[src->used_char - item_size]);

	for(int i = 0; i < item_size; i++)
		buffer[i] = start_ptr[i];

	src->cur_member--;

	src->used_char -= item_size;
	src->free_char += item_size;

	return;

}

