#include <stdlib.h>
//#include "radix_sort.h"
#include "breakers.h"

void radix_sort (long long* array, int size) {

	void_func_breaker(array != NULL)
	
	void_func_breaker(size > 0)

	int* remains = (int*) calloc (size, sizeof(int));
	void_func_breaker(remains != NULL)

	//temporary array that consists of subarrays
	//each subarray consists of elements with same digit for this iteration
	long long* tmp_array = (long long*) calloc (size, sizeof(long long));
	void_func_breaker(tmp_array != NULL)

	int border[10] = {0,0,0,0,0,0,0,0,0,0}; //borders between subarrays
	int starts[10] = {0,0,0,0,0,0,0,0,0,0}; //indicate where starts subarrays for each digit (0-9)

	long long next_digit = 1; //show that there are some nums with unmanufactured digits
	
	long long pow10 = 1;

	while(next_digit != 0) {
		
		next_digit = 0;
		
		//calculate remains for current array
		for (int i = 0; i < size; ++i) {
			remains[i] = (array[i] / pow10) % 10;

			if(next_digit < (array[i] / pow10)) {
				next_digit = (array[i] / pow10);
			}
		}

		//calculate number of each digit (0-9)
		for (int i = 0; i < size; ++i) {
			++border[remains[i]];
		}

		//set borders between future subarrays
		for (int i = 1; i < 10; ++i) {
			border[i] += border[i - 1];
			starts[i]  = border[i - 1];
		}

		//write elements in new order according to borders of subarrays
		for (int i = 0; i < size; ++i) {
			tmp_array[starts[remains[i]]] = array[i];
			
			++starts[remains[i]];
		}
	
		for (int i = 0; i < size; ++i) {
			array[i] = tmp_array[i];
		}

		pow10 *= 10;
		
		for (int i = 0; i < 10; ++i) {
			border[i] = 0;
			starts[i] = 0;
		}

	}

	free(remains  );
	free(tmp_array);

	return;

}

