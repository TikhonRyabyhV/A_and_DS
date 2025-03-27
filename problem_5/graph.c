#include <stdlib.h>
#include "graph.h"
#include "breakers.h"

//#define DEBUG

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

			else {
				return NO_EDGE;
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

		printf("Node %s (val = %d), edges: ", tmp_node->str, tmp_node->value);

		printf("\ninput: ");

		for (tmp_edge = tmp_node->input_edges.first_member; tmp_edge != NULL;
		     tmp_edge = tmp_edge->next_member                               ) {
			
			printf("%s -> %s (cap = %d, flow = %d) | ", tmp_edge->prev_node->str,
				       	           tmp_edge->next_node->str, tmp_edge->weight, tmp_edge->flow);

		}

		printf("\noutput: ");

		for (tmp_edge = tmp_node->output_edges.first_member; tmp_edge != NULL;
		     tmp_edge = tmp_edge->next_member                               ) {
			
			printf("%s -> %s (cap = %d, flow = %d) | ", tmp_edge->prev_node->str,
				              	   tmp_edge->next_node->str, tmp_edge->weight, tmp_edge->flow);

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
	
	// initialization
	node_st* tmp_node = src->nodes.first_member;

	while (tmp_node != NULL) {
		tmp_node->visit = NOT_VISITED;
		tmp_node->value = NOT_MARKED ;

		tmp_node = tmp_node->next_member;
	}
	// -----------------------------------------

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

void graph_Dijkstra (graph_st* src, node_st* start_node) {

	void_func_breaker(src        != NULL)
	void_func_breaker(start_node != NULL)

	// initialization
	node_st* tmp_node = src->nodes.first_member;

	while (tmp_node != NULL) {
		tmp_node->visit = NOT_VISITED;
		tmp_node->value = INF        ;

		tmp_node = tmp_node->next_member;
	}
	
	start_node->value = 0;

	int min = 0; // min value of not visited nodes
	node_st* current_node = NULL;
	edge_st* tmp_edge = NULL;

	tmp_node = start_node;

	// steps
	do {
		// work with current node
		tmp_edge = tmp_node->output_edges.first_member;

		while (tmp_edge != NULL) {
			if(tmp_edge->next_node->visit == NOT_VISITED &&
			  (tmp_edge->next_node->value == INF         ||
			   tmp_edge->next_node->value >  
			   (tmp_node->value + tmp_edge->weight))) {
				tmp_edge->next_node->value = tmp_node->value + tmp_edge->weight;	
			}

			tmp_edge = tmp_edge->next_member;
		}

		tmp_node->visit = VISITED;
		// ------------------------------------------------------------------------------
		
		// looking for nest node with low value
		min = INF;
		tmp_node = src->nodes.first_member;

		while (tmp_node != NULL) {
			if(((min > tmp_node->value && tmp_node->value != INF) ||
			              (min == INF && tmp_node->value != INF))
			               && tmp_node->visit == NOT_VISITED     ) {
				min = tmp_node->value;

				current_node = tmp_node;
			}
			
			tmp_node = tmp_node->next_member;
		}

		tmp_node = current_node;
		// -------------------------------------------------------------------------------

	} while (min != INF);

}

int min (int a, int b) {
	if(a < b) {
		return a;
	}

	else {
		return b;
	}

}

int graph_max_flow (graph_st* src, node_st* start_node, node_st* finish_node) {
	
	func_breaker(src != NULL)
	
	func_breaker(start_node  != NULL)
	func_breaker(finish_node != NULL)


	// intialization
	int C_min = (int)(1e9);

	node_st* tmp_node = src->nodes.first_member;

	while (tmp_node != NULL) {
		tmp_node->visit = NOT_VISITED;
		tmp_node->value = INF        ;

		tmp_node = tmp_node->next_member;
	}


	int result = 0, tmp = 0; // final and tmp results for flow

	// initialization of an array for some path
	int N = src->nodes.list_size;
	node_st** path = (node_st**) calloc (N, sizeof(node_st*));
	if(path == NULL) {
		return 0;
	}

	int i = 0; // path iterator
	edge_st* tmp_edge = NULL;

	while(tmp = DFS (src, start_node, finish_node, C_min, path, &i)) {
		result += tmp;

		
		// increase flow on founded path with low capacity
		
	#ifdef DEBUG
		//printf("i = %d\n", i);

		//for(int j = i - 1; j >= 0; --j) {
		//	printf("Node: %s\n", path[j]->str);
		//}
	#endif
		
		for(int j = i - 1; j > 0; --j) {
			
			tmp_edge = path[j]->output_edges.first_member;
				
			if(tmp_edge == NULL) {
				return 0;
			}

			while (tmp_edge->next_node != path[j - 1]) {
				tmp_edge = tmp_edge->next_member;
				
				if(tmp_edge->next_node == NULL) {
					return 0;
				}
			}

			tmp_edge->flow += tmp;

		}

	#ifdef DEBUG
		printf("tmp = %d\n", tmp);
		print_graph(src);
	#endif


		i = 0;
	}

	free(path);

	return result;

}


int DFS (graph_st* src, node_st* tmp_node, node_st* finish_node, int C_min, node_st** path, int* i) {

	func_breaker(src != NULL)
	
	func_breaker(tmp_node    != NULL)
	func_breaker(finish_node != NULL)
	
	// actions when we find finish node
	if(tmp_node == finish_node) {
		tmp_node->value = C_min;
		tmp_node->visit = VISITED;

		path[(*i)] = tmp_node;
		++(*i);

		return C_min;
	}

	// actions for other nodes
	tmp_node->visit = IN_PROCESS;

	// an array for variants of path from this node to finish node
	int N = src->nodes.list_size;
	node_st** local_path = (node_st**) calloc (N * N, sizeof(node_st*));
	if(local_path == NULL) {
		return 0;
	}

	int local_i = 0; // an iterator for this path


	int delta = 0, delta_min = 0; // min capacity of this path

	node_st* min_node = NULL;

	// find path with low capacity
	edge_st* tmp_edge = tmp_node->output_edges.first_member;
	while (tmp_edge != NULL) {
		if(tmp_edge->next_node->visit == NOT_VISITED &&
	           tmp_edge->flow < tmp_edge->weight           ) {
			delta = DFS (src, tmp_edge->next_node, finish_node,
				       	 min(C_min, tmp_edge->weight - tmp_edge->flow), local_path, &local_i);

			if(delta_min == 0 || delta_min > delta) {
				delta_min = delta;

				min_node = tmp_edge->next_node;
			}
		}
		
		if(tmp_edge->next_node->visit == VISITED) {
			tmp_edge->next_node->visit = NOT_VISITED;
		}

		tmp_edge = tmp_edge->next_member;
	}
	
	tmp_node->value = delta_min;
	
	/*tmp_edge = tmp_node->output_edges.first_member;
	while (tmp_edge != NULL) {
		if(tmp_edge->next_node->visit == VISITED) {
			tmp_edge->next_node->visit = NOT_VISITED;
		}

		tmp_edge = tmp_edge->next_member;
	}*/

	// add local path with low capacity to direct path
	int start = -1, finish = -1;
	int read_en = 0;

	for(int j = local_i - 1; j >= 0; --j) {
		if(local_path[j] == min_node) {
			finish = j;

			read_en = 1;
		}

		if(local_path[j] == finish_node && read_en == 1) {
			start = j;

			read_en = 0;

			continue;
		}
	}

	for(int j = start; j <= finish; ++j) {
	
		path[(*i)] = local_path[j];
		++(*i);
		
	}

	free(local_path);

	path[(*i)] = tmp_node;
	++(*i);

	tmp_node->visit = VISITED;

	return delta_min;

}
