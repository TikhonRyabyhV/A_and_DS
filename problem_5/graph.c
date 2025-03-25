#include <stdlib.h>
#include "graph.h"
//#include "stack.h"
#include "breakers.h"

void init_graph (graph_st* src) {
	
	void_func_breaker(src != NULL)

	init_node_list (&src->nodes);
	init_edge_list (&src->edges);

	return;

}


void graph_add_node (graph_st* src, char* name, int size) {

	void_func_breaker(src != NULL)
	void_func_breaker(name != NULL)
	
	void_func_breaker(size > 0)

	insert_node (&src->nodes, src->nodes.list_size + 1, name, size);

	return;

}

int graph_add_edge (graph_st* src, int weight, char* name_prev, char* name_next, int size_prev, int size_next) {

	func_breaker(src != NULL)
	
	func_breaker(name_prev != NULL)
	func_breaker(name_next != NULL)
	
	func_breaker(size_prev > 0)
	func_breaker(size_next > 0)

	node_st* prev_node = find_node (&src->nodes, name_prev, size_prev, NULL);
	node_st* next_node = find_node (&src->nodes, name_next, size_next, NULL);

	if(prev_node == NULL) {
		if(next_node == NULL) {
			return NO_A_B;
		}

		else {
			return NO_A;
		}
	}

	else {
		if(next_node == NULL) {
			return NO_B;
		}
	}

	insert_edge (&src->edges, src->edges.list_size + 1, weight, prev_node, next_node);
	
	insert_edge (&prev_node->output_edges, prev_node->output_edges.list_size + 1, weight, prev_node, next_node);
	insert_edge (&next_node-> input_edges, next_node-> input_edges.list_size + 1, weight, prev_node, next_node);

	return OK;

}

int graph_del_edge (graph_st* src, char* name_prev, char* name_next, int size_prev, int size_next) {
	
	func_breaker(src != NULL)

	func_breaker(name_prev != NULL)
	func_breaker(name_next != NULL)
	
	func_breaker(size_prev > 0)
	func_breaker(size_next > 0)

	int place = 0;
	edge_st* tmp = find_edge (&src->edges, name_prev, name_next, size_prev, size_next, &place);

	if(tmp == NULL) {
		node_st* prev_node = find_node (&src->nodes, name_prev, size_prev, NULL);
		node_st* next_node = find_node (&src->nodes, name_prev, size_prev, NULL);

		if(prev_node == NULL) {

			if(next_node == NULL) {
				return NO_A_B;
			}

			else {
				return NO_A;
			}

		}

		else {

			if(next_node == NULL) {
				return NO_B;
			}

		}

	}

	node_st* prev_node = tmp->prev_node;
	node_st* next_node = tmp->next_node;

	delete_edge (&src->edges, tmp, place);

	int place_in = 0, place_out = 0;

	edge_st*  input_edge = find_edge (&next_node-> input_edges,
					      name_prev, name_next, 
					      size_prev, size_next, &place_in);
	edge_st* output_edge = find_edge (&prev_node->output_edges,
					      name_prev, name_next,
					      size_prev, size_next, &place_out);

	func_breaker( input_edge != NULL)
	func_breaker(output_edge != NULL)

	delete_edge (&next_node-> input_edges,  input_edge, place_in );
	delete_edge (&prev_node->output_edges, output_edge, place_out);

	return OK;

}

int graph_del_node (graph_st* src, char* name, int size) {

	func_breaker(src != NULL)
	
	func_breaker(name != NULL)
	func_breaker(size >   0  )

	int node_place = 0;
	node_st* tmp = find_node (&src->nodes, name, size, &node_place);

	if(tmp == NULL) {
		return NO_A;
	}

	int edge_place = 0;
	edge_st* tmp_edge = NULL;
	edge_st* edge_iter = tmp->input_edges.first_member;
	
	while (edge_iter != NULL) {
		tmp_edge = find_edge (&edge_iter->prev_node->output_edges, 
				       edge_iter->prev_node->str,  tmp->str,
			               edge_iter->prev_node->size, tmp->size,
				                                  &edge_place);

		delete_edge (&edge_iter->prev_node->output_edges, tmp_edge, edge_place);

		tmp_edge = find_edge ( &src->edges, 
				       edge_iter->prev_node->str,  tmp->str,
			               edge_iter->prev_node->size, tmp->size,
				                                  &edge_place);
		
		delete_edge (&src->edges, tmp_edge, edge_place);

		tmp_edge = edge_iter;
		edge_iter = edge_iter->next_member;
		delete_edge (&tmp->input_edges, tmp_edge, 0);

	}


	edge_place = 0;
	edge_iter = tmp->output_edges.first_member;
	
	while (edge_iter != NULL) {
		tmp_edge = find_edge (&edge_iter->next_node->input_edges, 
				       tmp->str,  edge_iter->next_node->str,
			               tmp->size, edge_iter->next_node->size,
				                                  &edge_place);

		delete_edge (&edge_iter->next_node->input_edges, tmp_edge, edge_place);

		tmp_edge = find_edge ( &src->edges, 
				       tmp->str,  edge_iter->next_node->str,
			               tmp->size, edge_iter->next_node->size,
				                                  &edge_place);
		
		delete_edge (&src->edges, tmp_edge, edge_place);

		tmp_edge = edge_iter;
		edge_iter = edge_iter->next_member;
		delete_edge (&tmp->output_edges, tmp_edge, 0);
		

	}

	delete_node (&src->nodes, tmp, node_place);

	return OK;

}

void print_graph (graph_st* src) {
	
	void_func_breaker(src != NULL)

	node_st* tmp_node = NULL;
	edge_st* tmp_edge = NULL;	

	
	printf("\n============================================\n");
	printf("Current graph: \n");
	printf("\n-------------------------------\n\n");

	for (tmp_node = src->nodes.first_member; tmp_node != NULL;
             tmp_node = tmp_node->next_member                    ) {

		printf("Node %s, edges: ", tmp_node->str);

		printf("\ninput: ");

		for (tmp_edge = tmp_node->input_edges.first_member; tmp_edge != NULL;
		     tmp_edge = tmp_edge->next_member                               ) {
			
			printf("%s -> %s | ", tmp_edge->prev_node->str, tmp_edge->next_node->str);

		}

		printf("\noutput: ");

		for (tmp_edge = tmp_node->output_edges.first_member; tmp_edge != NULL;
		     tmp_edge = tmp_edge->next_member                               ) {
			
			printf("%s -> %s | ", tmp_edge->prev_node->str, tmp_edge->next_node->str);

		}

		printf("\n-------------------------------\n\n");
		
	}
	
	printf("\n============================================\n");

	return;

}

void destroy_graph (graph_st* src) {

	void_func_breaker(src != NULL)

	char* name = NULL;
	int size = 0;

	node_st* tmp = src->nodes.first_member;
	while (tmp != NULL) {
		name = tmp->str;
		size = tmp->size;

		tmp = tmp->next_member;

		graph_del_node (src, name, size);	
	}

	return;

}

void graph_RPO (graph_st* src, char_stack_st* order, edge_st** loops, int* loops_size, node_st* start_node) {
	
	void_func_breaker(src         != NULL)
	void_func_breaker(order       != NULL)
	void_func_breaker(loops       != NULL)
	void_func_breaker(loops_size  != NULL)
	void_func_breaker(start_node  != NULL)

	int N = src->nodes.list_size;

	node_st** queue = (node_st**) calloc( N, sizeof(node_st*));
	
	void_func_breaker(queue != NULL)

	int i = 0, j = 0; // i - iterator for queue, j - iterator for loops

	queue[i] = start_node;

	while (1) {
		if(queue[i]->value == queue[i]->output_edges.list_size) {
			
			if(i == 0) {
				put_item (order, queue[i]->str, queue[i]->size);
				break;	
			}

			else {
				put_item (order, queue[i]->str, queue[i]->size);
				
				--i;
				++(queue[i]->value);

				continue;
			}

		}

		if(queue[i]->value == NOT_MARKED) {
			
			if(queue[i]->output_edges.list_size == 0) {
				++(queue[i]->value);

				continue;
			}

			else {
				++(queue[i]->value);
			}

		}
		
		edge_st* tmp_edge = goto_edge (&queue[i]->output_edges, queue[i]->value + 1);

		++i;
		queue[i] = tmp_edge->next_node;

		if(queue[i]->value >= 0 && 
		   queue[i]->value < queue[i]->output_edges.list_size ) {
			loops[j] = tmp_edge;

			++j;
			--i;

			++(queue[i]->value);

			continue;
		}

		if(queue[i]->value == queue[i]->output_edges.list_size ) {
			--i;
			++(queue[i]->value);

			continue;
		}


	}

	(*loops_size) = j;

	free(queue);

	return;

}
