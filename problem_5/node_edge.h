#pragma once

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

typedef struct node {

        char* str ; // node ID
        int   size;

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

void init_edge_list (edge_list_st* src);

edge_st* goto_edge (edge_list_st* src, int place);

void insert_edge (edge_list_st* src, int range, int weight, node_st* prev_node, node_st* next_node);

void delete_edge (edge_list_st* src, int place);

void clear_edge_list (edge_list_st* src);

//----------------------------------------------------------------------------------------------------

int comp_str (char* a, char* b, int size);

void init_node_list (node_list_st* src);

node_st* goto_node (node_list_st* src, int place);

node_st* find_node (node_list_st* src, char* str, int size, int* place);

void insert_node (node_list_st* src, int range, char* str, int size);

void delete_node (node_list_st* src, int place);

void clear_node_list (node_list_st* src);

//----------------------------------------------------------------------------------------------------

