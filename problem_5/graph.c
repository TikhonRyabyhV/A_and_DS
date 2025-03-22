#include <stdlib.h>
#include "graph.h"
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

void print_graph (graph_st* src) {
	
	void_func_breaker(src != NULL)

	node_st* tmp_node = NULL;
	edge_st* tmp_edge = NULL;	

	for (int i = 0; i < src->nodes.list_size; ++i) {

		tmp_node = goto_node (&src->nodes, i + 1);

		printf("Node %s, edges: ", tmp_node->str);

		printf("\ninput: ");

		for (int j = 0; j < tmp_node->input_edges.list_size; ++j) {
			
			tmp_edge = goto_edge (&tmp_node->input_edges, j + 1);

			printf("%s -> %s | ", tmp_edge->prev_node->str, tmp_edge->next_node->str);

		}

		printf("\noutput: ");

		for (int j = 0; j < tmp_node->output_edges.list_size; ++j) {
			
			tmp_edge = goto_edge (&tmp_node->output_edges, j + 1);

			printf("%s -> %s | ", tmp_edge->prev_node->str, tmp_edge->next_node->str);

		}

		printf("\n");
		
	}

	return;

}
