#include <stdlib.h>
#include "sort.h"
#include "breakers.h"

void swap (int* a, int* b) {
	
	void_func_breaker(a != NULL)
	void_func_breaker(b != NULL)

	(*a) = (*a) ^ (*b);
	(*b) = (*b) ^ (*a);
	(*a) = (*a) ^ (*b);

	return;

}


void bubble_sort (int* array, int size) {
	
	void_func_breaker(array != NULL)

	void_func_breaker(size > 0)

#ifdef DEBUG
	int step = 0;

	printf("\nBubble sort:\n");
#endif

	for (int i = 1; i < size; ++i) {
		for (int j = 0; j < size - i; ++j) {
			if (array[j] > array[j + 1]) {
				swap (array + j, array + j + 1);
			}
		#ifdef DEBUG
			++step;

			printf("Step: %d. Array: \n[ ", step);
			for (int i = 0; i < size; ++i)
				printf("%d, ", array[i]);
			printf("]\n");
		#endif
		}
	}

	return;

}


void bubble_sort_check (int* array, int size) {
	
	void_func_breaker(array != NULL)

	void_func_breaker(size > 0)

#ifdef DEBUG
	int step = 0;

	printf("\nBubble sort with cheking:\n");
#endif

	int end = size - 1, end_tmp = 0;

	do {
		end_tmp = 0;

		for (int j = 0; j < end; ++j) {
			if (array[j] > array[j + 1]) {
				swap (array + j, array + j + 1);
				end_tmp = j;
			}
		}

		end = end_tmp;
		
	#ifdef DEBUG
		++step;

		printf("Step: %d. Array: \n[ ", step);
		for (int i = 0; i < size; ++i)
			printf("%d, ", array[i]);
		printf("]\n");
	#endif


	} while (end != 0);

	return;

}


void shaker_sort (int* array, int size) {
	
	void_func_breaker(array != NULL)

	void_func_breaker(size > 0)

#ifdef DEBUG
	int step = 0;

	printf("\nShaker sort:\n");
#endif

	int end = size - 1, start = 0;
	int end_tmp = 0, start_tmp = 0;

	do {
		end_tmp = 0;

		for (int j = start; j < end; ++j) {
			if (array[j] > array[j + 1]) {
				swap (array + j, array + j + 1);
				end_tmp = j;
			}
		}

		end = end_tmp;
		
		if(end == 0) {
			break;
		}

		start_tmp = 0;

		for (int j = end; j > start; --j) {
			if (array[j] < array[j - 1]) {
				swap (array + j, array + j - 1);
				start_tmp = j;
			}
		}

		start = start_tmp;
	
	#ifdef DEBUG
		++step;

		printf("Step: %d. Array: \n[ ", step);
		for (int i = 0; i < size; ++i)
			printf("%d, ", array[i]);
		printf("]\n");
	#endif

	} while (end != start);

	return;

}

void comb_sort (int* array, int size) {	
	
	void_func_breaker(array != NULL)

	void_func_breaker(size > 0)

	int swaps = 0;
	int step  = size;

	while(size > 1) {
		
		step /= 1.247f;

		if (step < 1) {
			step = 1;
		}

		swaps = 0;

		for (int i = 0; i + step < size; ++i) {
			if(array[i] > array[i + step]) {
				swap(array + i, array + i + step);
				swaps = i;
			}
		}

		if(step == 1) {
			size = swaps + 1;
		}
	}

	return;

}
