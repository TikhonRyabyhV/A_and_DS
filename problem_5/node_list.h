#pragma once

typedef struct node {
	
	char* str ; // node ID
	int   size;

	struct edge_list*  input_edges;
	struct edge_list* output_edges;

	struct node* prev_member;
	struct node* next_member;

} node_st;

typedef struct node_list {
	
	int list_size;

	node_st* first_member;
	node_st*  last_member;


} node_list_st;	

void init_node_list (node_list_st* src);

node_st* goto_node (node_list_st* src, int place);

void insert_node (node_list_st* src, int range, char* str, int size);

void delete_node (node_list_st* src, int place);

void clear_node_list (node_list_st* src);
