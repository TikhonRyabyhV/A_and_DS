#include <stdlib.h>
#include "graph.h"
#include "breakers.h"

int comp_str (char* a, char* b, int size) {

	func_breaker(size > 0)

	func_breaker(a != NULL)
	func_breaker(b != NULL)

	for(int i = 0; i < size; ++i) {
		if(a[i] != b[i]) {
			return 0;
		}
	}

	return 1;

}

void init_node_list (node_list_st* src) {
	
	void_func_breaker(src != NULL)

	src->list_size = 0;

	src->first_member = NULL;
	src->last_member  = NULL; 

	return;

}

node_st* goto_node (node_list_st* src, int place) {
	
	if(src == NULL)
		return NULL;

	if(src->list_size < place || place <= 0)
		return NULL;

	node_st* result = NULL;

	if(place < (src->list_size / 2)) {
		result = src->first_member;
		for(int i = 1; i < place; ++i)
		       result = result->next_member;	
	}

	else {
		result = src->last_member;
		for(int i = src->list_size; i > place; --i)
			result = result->prev_member;
	}

	return result;

}

node_st* find_node (node_list_st* src, char* str, int size, int* place) {

	if(src == NULL)
                return NULL;

        if(str == NULL || size <= 0)
                return NULL;

        node_st* result = NULL;

	result = src->first_member;

	int count = 1;

	while(result != NULL) {
		
		if(result->size == size) {
			if(comp_str(result->str, str, size)) {
				if(place != NULL) {
					(*place) = count;
				}

				return result;
			}
		}

		result = result->next_member;
		++count;

	}

	if(place != NULL) {
		(*place) = count;
	}

	return NULL;

}

int find_node_place (node_list_st* src, node_st* ptr) {

	func_breaker(src != NULL)
	func_breaker(ptr != NULL)

	node_st* tmp = src->first_member;
	int place = 1;

	while (tmp != NULL) {
		
		if(tmp == ptr) {
			return place;
		}

		else {
			tmp = tmp->next_member;
			++place;
		}

	}

	return 0;

}

void insert_node (node_list_st* src, int range, char* str, int size) {

	void_func_breaker(src != NULL)
	void_func_breaker(str != NULL)

	void_func_breaker(range > 0 && range < (src->list_size + 2))
	void_func_breaker(size  > 0)

	node_st* tmp = (node_st *) calloc(1, sizeof(node_st));
	void_func_breaker(tmp != NULL)

	init_edge_list (&tmp-> input_edges);
	init_edge_list (&tmp->output_edges);

	tmp->visit = NOT_VISITED;
	tmp->value = NOT_MARKED ;
		
	tmp->str = calloc(size, sizeof(char));
	void_func_breaker(tmp->str != NULL)

	tmp->size = size;
	for(int i = 0; i < size; ++i)
		tmp->str[i] = str[i];

	node_st *prev_member = NULL, *next_member = NULL;

	if(src->list_size > 0) {
		if(range == 1) {
			next_member = src->first_member;
			next_member->prev_member = tmp ;
			src->first_member = tmp        ;
		}

		else {
			if(range == (src->list_size + 1)) {
				prev_member = src->last_member;
				prev_member->next_member = tmp;
				src->last_member = tmp        ;
			}

			else {
				prev_member = goto_node(src, range - 1);
				next_member = goto_node(src, range    );

				void_func_breaker(prev_member != NULL)
				void_func_breaker(next_member != NULL)

				prev_member->next_member = tmp;
				next_member->prev_member = tmp;
			}
		}

	}

	else {
		src->first_member = tmp;
		src->last_member  = tmp;
	}

	tmp->prev_member = prev_member;
	tmp->next_member = next_member;

	src->list_size++;

	return;

}

void delete_node (node_list_st* src, node_st* ptr, int place) {
	
	void_func_breaker(src != NULL)

	void_func_breaker(place >= 0 && place < (src->list_size + 1))
	
	node_st* tmp = ptr;
	if(ptr == NULL) {
		tmp = goto_node(src, place);
		void_func_breaker(tmp != NULL)
	}

	else {
		if(place == 0) {
			place = find_node_place (src, ptr);
			void_func_breaker(place > 0)
		}
	}

	node_st *prev_member = NULL, *next_member = NULL;

	if(place == 1) {
		if(src->list_size == 1)	{
			src->first_member = NULL;
			src->last_member  = NULL; 
		}

		else {
			next_member = tmp->next_member ;
			next_member->prev_member = NULL;
			src->first_member = next_member;
		}
	}

	else {
		if(place == src->list_size) {
			prev_member = tmp->prev_member ;
			prev_member->next_member = NULL;
			src->last_member = prev_member ;
		}

		else {
			prev_member = tmp->prev_member;
			next_member = tmp->next_member;

			void_func_breaker(prev_member != NULL)
			void_func_breaker(next_member != NULL)

			prev_member->next_member = next_member;
			next_member->prev_member = prev_member;
		}
	}


	void_func_breaker(tmp->str != NULL)
	free(tmp->str);

	free(tmp);

	src->list_size--;

	return;

}

void clear_node_list (node_list_st* src) {
	
	void_func_breaker(src != NULL)

	while(src->list_size != 0)
		delete_node(src, NULL, src->list_size);

	return;

}
