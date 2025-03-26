#include <stdio.h>
#include "graph.h"
#include "breakers.h"

#define MAX_SIZE 200
#define MAX_NUM 1000000

int get_command (char* src, char** end) {
	
	func_breaker(src != NULL)
	
	char* commands[] = {"NODE", "EDGE", "REMOVE NODE", "REMOVE EDGE",
	       	            "RPO_NUMBERING", "DIJKSTRA", "PRINT", "DESTROY", "STOP", "MAX FLOW"};
	int sizes[] = {4, 4, 11, 11, 13, 8, 5, 7, 4, 8};

	int start = 0;
	int i = 0;

	while (!('A' <= src[i] && src[i] <= 'Z') && src[i] != '_') {
		if(src[i] == '\n') {
			return 0;
		}

		++i;
	}

	start = i;

	while (('A' <= src[i] && src[i] <= 'Z') || src[i] == '_') {
		++i;
	}

	if(comp_str(src + start, "REMOVE", i - start)) {
		
		while (!('A' <= src[i] && src[i] <= 'Z') && src[i] != '_') {
			if(src[i] == '\n') {
				return 0;
			}

			++i;
		}

		start = i;

		while (('A' <= src[i] && src[i] <= 'Z') || src[i] == '_') {
			++i;
		}

		(*end) = src + i;

		return 3 * comp_str(src + start, "NODE", i - start) + 
		       4 * comp_str(src + start, "EDGE", i - start);
	}
	
	if(comp_str(src + start, "MAX", i - start)) {
		
		while (!('A' <= src[i] && src[i] <= 'Z') && src[i] != '_') {
			if(src[i] == '\n') {
				return 0;
			}

			++i;
		}

		start = i;

		while (('A' <= src[i] && src[i] <= 'Z') || src[i] == '_') {
			++i;
		}

		(*end) = src + i;

		return 10 * comp_str(src + start, "FLOW", i - start);
	}

	(*end) = src + i;

	int result = 0;

	for(int j = 0; j < 9; ++j) {
		if(i - start == sizes[j]) {
			result += (j + 1) * comp_str(src + start, commands[j], sizes[j]); 
		}
	}

	return result;

}

int get_num (char* src) {

	func_breaker(src != NULL)

	int i = 0, j = 0, res = 0;

	while(!('1' <= src[i] && src[i] <= '9')) {
		if(src[i] == '\n') {
			return -1;
		}

		++i;
	}

	char buffer[100];

	while(('1' <= src[i] && src[i] <= '9') || src[i] == '0') {
		buffer[j] = src[i];
		++i;
		++j;
	}

	buffer[j] = '\0';

	res = atoi(buffer);

	if(res > MAX_NUM)
		return -1 ;
	else
		return res;

}

int get_args (char* src, int* arg, char* str_1, char* str_2, int* size_1, int* size_2) {
	
	func_breaker(src    != NULL)
	func_breaker(arg    != NULL)
	func_breaker(str_1  != NULL)
	func_breaker(str_2  != NULL)
	func_breaker(size_1 != NULL)
	func_breaker(size_2 != NULL)

	int start = 0;
	int i = 0;

	while (!('A' <= src[i] && src[i] <= 'Z') && !('a' <= src[i] && src[i] <= 'z')) {
		if(src[i] == '\n') {
			return 0;
		}

		++i;
	}

	start = i;
	(*size_1) = 0;

	while (('A' <= src[i] && src[i] <= 'Z') || ('a' <= src[i] && src[i] <= 'z')) {
		str_1[(*size_1)] = src[i];
		
		++(*size_1);
		++i;
	}

	str_1[(*size_1)] = '\0';
	++(*size_1);

	while (!('A' <= src[i] && src[i] <= 'Z') && !('a' <= src[i] && src[i] <= 'z')) {
		if(src[i] == '\n') {
			return 1;
		}

		++i;
	}

	start = i;
	(*size_2) = 0;

	while (('A' <= src[i] && src[i] <= 'Z') || ('a' <= src[i] && src[i] <= 'z')) {
		str_2[(*size_2)] = src[i];
		
		++(*size_2);
		++i;
	}
	str_2[(*size_2)] = '\0';
	++(*size_2);

	(*arg) = get_num (src + i);

	if((*arg) < 0) {
		return 2;
	}

	else {
		return 3;
	}

}

int main () {

	graph_st graph;

	init_graph (&graph);

	char* input_str = (char*) calloc (MAX_SIZE, sizeof(char));
	func_breaker(input_str != NULL)

	int command = 0;
	int arg = 0;
	char str_1[256], str_2[256];
	int  size_1 = 0, size_2 = 0;
	int res = 0;	

	char* ptr = NULL;

	int errors = OK;

	int stop = 0;

	char_stack_st order;
	edge_st** loops = NULL;
	int loops_size = 0;

	int N = 0; // nodes number
	char buffer[256];

	do {
		ptr = NULL;
		res = 0;
		errors = OK;


		func_breaker(input_str == fgets(input_str, MAX_SIZE, stdin))

		command = get_command(input_str, &ptr);

		if(ptr != NULL) {
			res = get_args(ptr, &arg, str_1, str_2, &size_1, &size_2);
		}

		switch (command) {
			case 1:
				if (res == 1) {
					graph_add_node (&graph, str_1, size_1);
				}

				break;

			case 2:
				if (res == 3) {
					errors = graph_add_edge (&graph, arg, str_1, str_2, size_1, size_2);
				
					switch (errors) {
						case OK:
							break;

						case NO_A:
							printf("Unknown node %s\n", str_1);
							break;

						case NO_B:
							printf("Unknown node %s\n", str_2);
							break;

						case NO_A_B:
							printf("Unknown nodes %s %s\n", str_1, str_2);
							break;

						default:
							break;
					}
				}

				break;

			case 3:
				if (res == 1) {
					errors = graph_del_node (&graph, str_1, size_1);

					switch (errors) {
						case OK:
							break;

						case NO_A:
							printf("Unknown node %s\n", str_1);
							break;

						default:
							break;
					}
				}

				break;

			case 4:
				if (res == 2) {
					errors = graph_del_edge (&graph, str_1, str_2, size_1, size_2);
				
					switch (errors) {
						case OK:
							break;

						case NO_A:
							printf("Unknown node %s\n", str_1);
							break;

						case NO_B:
							printf("Unknown node %s\n", str_2);
							break;

						case NO_A_B:
							printf("Unknown nodes %s %s\n", str_1, str_2);
							break;

						case NO_EDGE:
							graph_del_edge (&graph, str_2, str_1, size_2, size_1);
							break;

						default:
							break;
					}
				}

				break;

			case 5:
				if (res == 1) {
					N = graph.nodes.list_size;

					create_stack (&order, N * 2, N);

					loops = (edge_st**) calloc((N * (N - 1)) / 2, sizeof(edge_st*));
					loops_size = 0;

					buffer[0] = '\0';

					node_st* start_node = find_node (&graph.nodes, str_1, size_1, NULL);

					graph_RPO (&graph, &order, loops, &loops_size, start_node);


					int end_i = order.cur_member + 1;
					for(int i = 0; i < end_i; ++i) {
						get_item (&order, buffer);

						printf("%s ", buffer);
					}
					printf("\n");

					destroy_stack (&order);


					for(int i = 0; i < loops_size; ++i) {
						printf("Found loop: %s->%s\n", 
					        	loops[i]->next_node->str,
					       		loops[i]->prev_node->str);
					}

					free(loops);
				}

				break;

			case 6:
				if (res == 1) {
					node_st* start_node = find_node (&graph.nodes, str_1, size_1, NULL);

					if(start_node == NULL) {
						break;
					}

					graph_Dijkstra (&graph, start_node);

					node_st* tmp_node = graph.nodes.first_member;

					while (tmp_node != NULL) {
						if(tmp_node != start_node) {
							printf("%s %d\n", tmp_node->str, tmp_node->value);
						}

						tmp_node = tmp_node->next_member;
					}
				}

				break;

			case 7:
				print_graph (&graph);
				
				break;

			case 8:
				destroy_graph(&graph);

				break;

			case 9:
				stop = 1;

				break;

			case 10:
				if (res == 2) {
					node_st*  start_node = find_node (&graph.nodes, str_1, size_1, NULL);
					node_st* finish_node = find_node (&graph.nodes, str_2, size_2, NULL);
					
					if(start_node == NULL || finish_node == NULL) {
						break;
					}
					
					int flow = 0;

					flow = graph_max_flow(&graph, start_node, finish_node);

					printf("%d\n", flow);
				}

				break;

			default:
				
				break;
		}

	} while (stop != 1);

	destroy_graph (&graph);

	free(input_str);
}
