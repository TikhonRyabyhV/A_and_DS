#include <stdlib.h>
#include <algorithm>
#include "radix_sort.h"
#include "breakers.h"

void shuffle_array (long long* array, int size, int shuff_part) {
	
	void_func_breaker(array != NULL)

	void_func_breaker(size > 0)
	void_func_breaker(shuff_part >= 0 && shuff_part <= 100)

	srand(time(NULL));
	int j = 0;

	double tmp = ((double) shuff_part) / 100 * ((double) size);

	int stop = size - ((int) tmp) + 1;

	for (int i = size - 1; i >= stop; --i) {
		j = rand() % (i + 1);
		
		long long add = array[j];
		array[j] = array[i];
		array[i] = add;
	
	}

	return;

}

void copy_array (long long* src, long long* dst, int size) {
	
	void_func_breaker(src != NULL)
	void_func_breaker(dst != NULL)
	
	void_func_breaker(size > 0)

	for (int i = 0; i < size; ++i) {
		dst[i] = src[i];
	}

	return;

}

int cmp_array (long long* a, long long* b, int size) {
	
	func_breaker(a != NULL)
	func_breaker(b != NULL)
	
	func_breaker(size > 0)

	for (int i = 0; i < size; ++i) {
		if(a[i] != b[i]) {

			//printf ("Diff: a[%d] = %d, b[%d] = %d.\n", i, a[i], i, b[i]);
			return 0;
		}
	}

	return 1;

}

long long power (long long base, int exp) {
	
	long long res = 1;

	for(int i = 0; i < exp; ++i) {
		res *= base;
	}

	return res;

}

int main () {

	long long* input_arr  = NULL;
	long long* output_arr = NULL;
	long long* expect_arr = NULL;

	FILE *file;
	
	int count = 0;

	unsigned long long TimeValue = 0;
	
	unsigned long long* work_time = calloc (24, sizeof(unsigned long long));
	func_breaker(work_time != NULL)


	for (int i = 1; i < 13; ++i) {
		
		count = 0;
			
		input_arr = calloc (ARR_SIZE, sizeof(long long));
		func_breaker(input_arr != NULL)
			
		output_arr = calloc (ARR_SIZE, sizeof(long long));
		func_breaker(output_arr != NULL)
			
		expect_arr = calloc (ARR_SIZE, sizeof(long long));
		func_breaker(expect_arr != NULL)

		long long pow10 = power (10, i    );
		long long base  = power (10, i - 1);
		for (int k = 0; k < ARR_SIZE; ++k) {
			input_arr [k] = (base + k) % pow10;
			expect_arr[k] = (base + k) % pow10;
		}

		shuffle_array (input_arr, ARR_SIZE, 100);

		
		{
		copy_array (input_arr, output_arr, ARR_SIZE);
				
		clock_t start = clock();
		radix_sort (output_arr, ARR_SIZE);
		work_time [0 * 5 + i - 1] = clock() - start;


		if(cmp_array (expect_arr, output_arr, j)) {
				printf ("Chaos: 100 %%, digits: %d, sort: radix, res: ok.\n", i);
				printf ("Time: %llu.\n", work_time [5 * 0 + i - 1]);	
				++count;
		}

		else {
				printf ("Chaos: 100 %%, digits: %d, sort: radix, res: fail.\n", i); 
		}
		}
		
		{
		copy_array (input_arr, output_arr, ARR_SIZE);
				
		clock_t start = clock();
		std::sort (output_arr, output_arr + ARR_SIZE);
		work_time [1 * 5 + i - 1] = clock() - start;


		if(cmp_array (expect_arr, output_arr, j)) {
				printf ("Chaos: 100 %%, digits: %d, sort: C++ sort, res: ok.\n", i);
				printf ("Time: %llu.\n", work_time [1 * 0 + i - 1]);	
				++count;
		}

		else {
				printf ("Chaos: 100 %%, digits: %d, sort: C++ sort, res: fail.\n", i); 
		}
		}

		free(input_arr );
		free(output_arr);
		free(expect_arr);
	}
			
	if(count == 24) {

		printf ("-----------------------\n");
		file = fopen ("digits_dep.txt", "w");

		func_breaker(file != NULL)

		for (int n = 0; n < 2; ++n) {
			for (int m = 0; m < 13; ++m) {
				fprintf (file, "%llu ", work_time[n * 5 + m]);
			}

			fprintf (file, "\n");
		}
	}

	fclose(file);
	free(work_time);

	return 0;

}
