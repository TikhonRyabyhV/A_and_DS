#include <stdlib.h>
#include "graph.h"
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

	edge_st* result = src->first_member;
	--place;

	while (place > 0) {
		result = result->next_member;
		--place;
	}

	return result;

}

edge_st* find_edge (edge_list_st* src, char* prev_name, char* next_name, int prev_size, int next_size, int* place) {

	if(src == NULL || prev_name == NULL || next_name == NULL)
		return NULL;
	
	if(prev_size <= 0 || next_size <= 0)
		return NULL;

	edge_st* tmp = src->first_member;

	int cnt = 1;

	while (tmp != NULL) {
		
		if(tmp->prev_node->size == prev_size &&
		   tmp->next_node->size == next_size   ) {
		
			if(comp_str(tmp->prev_node->str, prev_name, prev_size) &&
			   comp_str(tmp->next_node->str, next_name, next_size)   ) {

				if(place != NULL) {
					(*place) = cnt;
				}

				return tmp;

			}

		}

		tmp = tmp->next_member;
		++cnt;
	
	}

	return tmp;

}

int find_edge_place (edge_list_st* src, edge_st* ptr) {
	
	func_breaker(src != NULL)
	func_breaker(ptr != NULL)

	edge_st* tmp = src->first_member;
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

void insert_edge (edge_list_st* src, int range, int weight, int type, node_st* prev_node, node_st* next_node) {

	void_func_breaker(src != NULL)
	
	void_func_breaker(prev_node != NULL)
	void_func_breaker(next_node != NULL)

	void_func_breaker(range > 0 && range < (src->list_size + 2))

	edge_st* tmp = (edge_st *) calloc(1, sizeof(edge_st));
	void_func_breaker(tmp != NULL)

	tmp->weight = weight;
	tmp->type   = type  ;
	tmp->flow   = 0;

	tmp->prev_node = prev_node;
	tmp->next_node = next_node;

	edge_st *prev_member = NULL, *next_member = NULL;

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
				prev_member = goto_edge(src, range - 1);
				next_member = goto_edge(src, range    );

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

void delete_edge (edge_list_st* src, edge_st* ptr, int place) {
	
	void_func_breaker(src != NULL)

	void_func_breaker(place >= 0 && place < (src->list_size + 1))
	
	edge_st* tmp = ptr;
	if(ptr == NULL) {
		tmp = goto_edge(src, place);
		void_func_breaker(tmp != NULL)
	}

	else {
		if(place == 0) {
			place = find_edge_place (src, ptr);
			void_func_breaker(place > 0)
		}
	}

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
		delete_edge(src, NULL, src->list_size);

	return;

}
