#include <stdio.h>
#include "graph.h"

int main() {

	graph_st my_graph;

	init_graph(&my_graph);

	printf("OK\n");
	graph_add_node (&my_graph, "A", 2);
	graph_add_node (&my_graph, "B", 2);
	graph_add_node (&my_graph, "C", 2);
	
	printf("OK\n");
	print_graph (&my_graph);

	printf("OK\n");
	graph_add_edge (&my_graph, 1, "A", "B", 2, 2);
	graph_add_edge (&my_graph, 5, "B", "C", 2, 2);
	graph_add_edge (&my_graph, 9, "A", "C", 2, 2);
	graph_add_edge (&my_graph, 6, "B", "A", 2, 2);
	printf("OK\n");

	print_graph (&my_graph);

	return 0;
}
