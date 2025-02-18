#include <stdio.h>
#include "list.h"
#include "breakers.h"

int main() {

	list_head_st my_list;
	init_list (&my_list);

	char* string[5] = {"hello", "asd", "upfgh", "1", "jojojdojdojodjj"};
	list_member_st* tmp = NULL;

	for(int i = 0; i < 2; ++i)
		insert_member (&my_list, i + 1, string[i], 17);

	for(int i = 0; i < 2; ++i) {
		tmp = goto_member (&my_list, i + 1);
		func_breaker(tmp != NULL)
		printf("Member %d: %s\n", i + 1, tmp->str);
	}
		printf("---------------------------------------\n");

	printf("OK\n");
	insert_member (&my_list, 1, string[2], 17);
	for(int i = 0; i < 3; ++i) {
		tmp = goto_member (&my_list, i + 1);
		printf("Member %d: %s\n", i + 1, tmp->str);
	}
		printf("---------------------------------------\n");

	insert_member (&my_list, 4, string[4], 17);
	for(int i = 0; i < 4; ++i) {
		tmp = goto_member (&my_list, i + 1);
		printf("Member %d: %s\n", i + 1, tmp->str);
	}
		printf("---------------------------------------\n");

	insert_member (&my_list, 3, string[3], 17);
	printf("OK\n");


	for(int i = 0; i < 5; ++i) {
		tmp = goto_member (&my_list, i + 1);
		printf("Member %d: %s\n", i + 1, tmp->str);
	}
		printf("---------------------------------------\n");

	delete_member (&my_list, 4);
	for(int i = 0; i < 4; ++i) {
		tmp = goto_member (&my_list, i + 1);
		printf("Member %d: %s\n", i + 1, tmp->str);
	}
		printf("---------------------------------------\n");

	delete_member (&my_list, 4);
	for(int i = 0; i < 3; ++i) {
		tmp = goto_member (&my_list, i + 1);
		printf("Member %d: %s\n", i + 1, tmp->str);
	}
		printf("---------------------------------------\n");

	delete_member (&my_list, 1);
	for(int i = 0; i < 2; ++i) {
		tmp = goto_member (&my_list, i + 1);
		printf("Member %d: %s\n", i + 1, tmp->str);
	}
		printf("---------------------------------------\n");

	clear_list (&my_list);
	printf("List: size - %d\n", my_list.list_size);
	
	return 0;

}
