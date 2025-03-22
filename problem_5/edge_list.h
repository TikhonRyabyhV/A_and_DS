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

void init_edge_list (edge_list_st* src);

edge_st* goto_edge (edge_list_st* src, int place);

void insert_edge (edge_list_st* src, int range, int weight, node_st* prev_node, node_st* next_node);

void delete_edge (edge_list_st* src, int place);

void clear_edge_list (edge_list_st* src);
