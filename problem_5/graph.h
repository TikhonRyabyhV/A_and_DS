#pragma once
#include "stack.h"

typedef struct edge {

	int   weight;

	struct node* prev_node;
	struct node* next_node;

	struct edge* prev_member;
	struct edge* next_member;

} edge_st;

typedef struct edge_list {

	int list_size;

	edge_st* first_member;
	edge_st* last_member ;


} edge_list_st;

//----------------------------------------------------------------------------------------------------

#define NOT_MARKED 0-1

typedef struct node {

        char* str ; // node ID
        int   size;

	int value;

        struct edge_list  input_edges;
        struct edge_list output_edges;

        struct node* prev_member;
        struct node* next_member;

} node_st;

typedef struct node_list {

        int list_size;

        node_st* first_member;
        node_st*  last_member;


} node_list_st;

//----------------------------------------------------------------------------------------------------

#define OK     0-1
#define NO_A   0-2
#define NO_B   0-3
#define NO_A_B 0-4


typedef struct graph {

	struct node_list nodes;
	struct edge_list edges; 

} graph_st;

//----------------------------------------------------------------------------------------------------

void init_edge_list (edge_list_st* src);

edge_st* goto_edge (edge_list_st* src, int place);

edge_st* find_edge (edge_list_st* src, char* prev_name, char* next_name, int prev_size, int next_size, int* place);

int find_edge_place (edge_list_st* src, edge_st* ptr);

void insert_edge (edge_list_st* src, int range, int weight, node_st* prev_node, node_st* next_node);

void delete_edge (edge_list_st* src, edge_st* ptr, int place);

void clear_edge_list (edge_list_st* src);

//----------------------------------------------------------------------------------------------------

int comp_str (char* a, char* b, int size);

void init_node_list (node_list_st* src);

node_st* goto_node (node_list_st* src, int place);

node_st* find_node (node_list_st* src, char* str, int size, int* place);

int find_node_place (node_list_st* src, node_st* ptr);

void insert_node (node_list_st* src, int range, char* str, int size);

void delete_node (node_list_st* src, node_st* ptr, int place);

void clear_node_list (node_list_st* src);

//----------------------------------------------------------------------------------------------------

void init_graph  (graph_st* src);

void print_graph (graph_st* src);

void graph_add_node (graph_st* src, char* name, int size);

int  graph_add_edge (graph_st* src, int weight, 
		     char* name_prev, char* name_next,
		     int size_prev, int size_next);

int graph_del_node (graph_st* src, char* name, int size);

int graph_del_edge (graph_st* src, char* name_prev, char* name_next, int size_prev, int size_next);

void destroy_graph (graph_st* src);

void graph_RPO (graph_st* src, char_stack_st* order, edge_st** loops, int* loops_size, node_st* start_node);

//----------------------------------------------------------------------------------------------------

