#include <stdlib.h>
#include "edge_list.h"
#include "node_list.h"
#include "breakers.h"

void init_edge_list (edge_list_st* src) {
	
	void_func_breaker(src != NULL)

	src->list_size = 0;

	src->first_member = NULL;
	src->last_member  = NULL; 

	return;

}

edge_st* goto_edge (edge_list_st* src, int place) {
	
	if(src == NULL)
		return NULL;

	if(src->list_size < place || place <= 0)
		return NULL;

	edge_st* result = NULL;

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

void insert_edge (edge_list_st* src, int range, int weight, node_st* prev_node, node_st* next_node) {

	void_func_breaker(src != NULL)
	
	void_func_breaker(prev_node != NULL)
	void_func_breaker(next_node != NULL)

	void_func_breaker(range > 0 && range < (src->list_size + 2))

	node_st* tmp = (node_st *) calloc(1, sizeof(node_st));
	void_func_breaker(tmp != NULL)

	tmp->weight = weight;

	tmp->prev_node = prev_node;
	tmp->next_node = next_node;

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
				prev_member = goto_member(src, range - 1);
				next_member = goto_member(src, range    );

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

void delete_edge (edge_list_st* src, int place) {
	
	void_func_breaker(src != NULL)

	void_func_breaker(place > 0 && place < (src->list_size + 1))
	
	list_member_st *tmp = goto_edge(src, place);
	void_func_breaker(tmp != NULL)

	edge_st *prev_member = NULL, *next_member = NULL;

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


	free(tmp);

	src->list_size--;

	return;

}

void clear_edge_list (edge_list_st* src) {
	
	void_func_breaker(src != NULL)

	while(src->list_size != 0)
		delete_member(src, src->list_size);

	return;

}
