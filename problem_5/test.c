#include <stdio.h>
#include "graph.h"
//#include "stack.h"

int main() {

	graph_st my_graph;

	init_graph(&my_graph);

	// ---------------------------------------------
	graph_add_node (&my_graph, "A", 2);
	graph_add_node (&my_graph, "B", 2);
	graph_add_node (&my_graph, "C", 2);
	graph_add_node (&my_graph, "D", 2);
	
	print_graph (&my_graph);

	// ---------------------------------------------
	graph_add_edge (&my_graph, 2, "A", "B", 2, 2);
	graph_add_edge (&my_graph, 7, "B", "C", 2, 2);
	//graph_add_edge (&my_graph, 2, "A", "C", 2, 2);
	graph_add_edge (&my_graph, 5, "A", "D", 2, 2);
	graph_add_edge (&my_graph, 9, "C", "D", 2, 2);
	//graph_add_edge (&my_graph, 6, "B", "A", 2, 2);
	
	print_graph (&my_graph);

	// ---------------------------------------------
	char_stack_st order;

	int N = my_graph.nodes.list_size;
	int E = my_graph.edges.list_size;
	
	create_stack (&order, N * 2, N);
	
	edge_st** loops = (edge_st**) calloc((N * (N - 1)) / 2, sizeof(edge_st*));	
	int loops_size = 0;

	char buffer[256];
	buffer[0] = '\0';

	node_st* start_node = find_node (&my_graph.nodes, "A", 2, NULL);

	graph_RPO (&my_graph, &order, loops, &loops_size, start_node);

	
	for(int i = 0; i < N; ++i) {
		get_item (&order, buffer);

		printf("%s ", buffer);
	}
	printf("\n");

	destroy_stack (&order);

	printf("Loops size: %d\n", loops_size);

	for(int i = 0; i < loops_size; ++i) {
		printf("Found loop: %s->%s\n", loops[i]->next_node->str, loops[i]->prev_node->str);
	}
	
	free(loops);
	// ---------------------------------------------

	graph_Dijkstra (&my_graph, start_node);

	node_st* tmp_node = my_graph.nodes.first_member;

	while (tmp_node != NULL) {
		printf("%s %d\n", tmp_node->str, tmp_node->value);

		tmp_node = tmp_node->next_member;
	}

	// ---------------------------------------------
	node_st* finish_node = find_node (&my_graph.nodes, "D", 2, NULL);
	int flow = 0;

	flow = graph_max_flow(&my_graph, start_node, finish_node);

	printf("Flow: %d\n", flow);
	// ---------------------------------------------
	graph_del_edge (&my_graph, "B", "A", 2, 2);
	
	print_graph (&my_graph);

	// ---------------------------------------------
	graph_del_node (&my_graph, "B", 2);

	print_graph (&my_graph);
	
	// ---------------------------------------------
	destroy_graph(&my_graph);

	print_graph (&my_graph);

	return 0;
}
