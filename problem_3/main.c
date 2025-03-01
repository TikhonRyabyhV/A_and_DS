#include <stdio.h>
#include "sort.h"
#include "breakers.h"


int main () {

	{
		int array[10] = {6, 7, 9, 0, 6, 4, 3, 1, 2, 8};

		printf("Input array: \n[ ");
		for (int i = 0; i < 10; ++i)
			printf("%d, ", array[i]);
		printf("]\n");

		bubble_sort (array, 10);

		printf("Output array: \n[ ");
		for (int i = 0; i < 10; ++i)
			printf("%d, ", array[i]);
		printf("]\n");

		printf("-----------------------------------");
	}

	{
		int array[10] = {6, 7, 9, 0, 6, 4, 3, 1, 2, 8};

		printf("Input array: \n[ ");
		for (int i = 0; i < 10; ++i)
			printf("%d, ", array[i]);
		printf("]\n");

		bubble_sort_check (array, 10);

		printf("Output array: \n[ ");
		for (int i = 0; i < 10; ++i)
			printf("%d, ", array[i]);
		printf("]\n");
		
		printf("-----------------------------------");
	}

	{
		int array[10] = {6, 7, 9, 0, 6, 4, 3, 1, 2, 8};

		printf("Input array: \n[ ");
		for (int i = 0; i < 10; ++i)
			printf("%d, ", array[i]);
		printf("]\n");

		shaker_sort (array, 10);

		printf("Output array: \n[ ");
		for (int i = 0; i < 10; ++i)
			printf("%d, ", array[i]);
		printf("]\n");
		
		printf("-----------------------------------");
	}


	return 0;

}
