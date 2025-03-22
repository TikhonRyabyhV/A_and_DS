#pragma once
#include "node_edge.h"

#define OK     0-1
#define NO_A   0-2
#define NO_B   0-3
#define NO_A_B 0-4


typedef struct graph {

	struct node_list nodes;
	struct edge_list edges; 

} graph_st;

void init_graph  (graph_st* src);

void print_graph (graph_st* src);

void graph_add_node (graph_st* src, char* name, int size);

int  graph_add_edge (graph_st* src, int weight, 
		     char* name_prev, char* name_next,
		     int size_prev, int size_next);

int graph_del_node (graph_st* src, char* name, int size);

int graph_del_edge (graph_st* src, char* name_prev, char* name_next, int size_prev, int size_next);
