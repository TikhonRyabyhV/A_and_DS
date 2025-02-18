#pragma once

typedef struct list_member {
	
	char* str ;
	int   size;

	struct list_member* prev_member;
	struct list_member* next_member;

} list_member_st;

typedef struct list_head {
	
	int list_size;

	list_member_st* first_member;
	list_member_st* last_member ;


} list_head_st;	

void init_list (list_head_st* src);

list_member_st* goto_member (list_head_st* src, int place);

void insert_member (list_head_st* src, int range, char* str, int size);

void delete_member (list_head_st* src, int place);

void clear_list (list_head_st* src);
