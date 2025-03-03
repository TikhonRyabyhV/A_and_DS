#include <stdlib.h>
//#include "radix_sort.h"
#include "breakers.h"

void radix_sort (long long* array, int size) {

	void_func_breaker(array != NULL)
	
	void_func_breaker(size > 0)

	int* remains = (int*) calloc (size, sizeof(int));
	void_func_breaker(remains != NULL)

	long long* tmp_array = (long long*) calloc (size, sizeof(long long));
	void_func_breaker(tmp_array != NULL)

	int border[10] = {0,0,0,0,0,0,0,0,0,0};
	int starts[10] = {0,0,0,0,0,0,0,0,0,0};

	long long next_digit = 1;
	
	long long pow10 = 1;

	while(next_digit != 0) {
		
		next_digit = 0;
		
		for (int i = 0; i < size; ++i) {
			remains[i] = (array[i] / pow10) % 10;

			if(next_digit < (array[i] / pow10)) {
				next_digit = (array[i] / pow10);
			}
		}

		for (int i = 0; i < size; ++i) {
			++border[remains[i]];
		}

		for (int i = 1; i < 10; ++i) {
			border[i] += border[i - 1];
			starts[i]  = border[i - 1];
		}

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

