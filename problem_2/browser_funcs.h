#pragma once

#define MAX_SIZE 40
#define MAX_URL  21
#define MAX_NUM  100

#define NOP     0
#define VISIT   1
#define BACK    2
#define FORWARD 3

typedef struct command {

	char* arg_str ;
	int   arg_size;
	int   arg_num ;
	int   opcode  ;

} command_st;

int comp_str (char* a, char* b, int size);

int get_num (char* src, int max_num);

int get_URL (char* src, char* dst, int dst_size);

void get_command (command_st* dst, char* src, int size);

int grow_history (char** src, int size);
