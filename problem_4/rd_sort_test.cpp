#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "radix_sort.h"
#include "breakers.h"

#define ARR_SIZE 100000
#define START_DIGIT 6
#define END_DIGIT   18
#define DIGIT_LEN   (END_DIGIT - START_DIGIT + 1)

//shuffle array using the Fisher-Yates algorithm 
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
	
	unsigned long long* work_time = (unsigned long long*) calloc (2 * DIGIT_LEN, sizeof(unsigned long long));
	func_breaker(work_time != NULL)


	//cycle for test, how speeds of these algorithms depend on digit number
	for (int i = START_DIGIT; i <= END_DIGIT; ++i) {
		
		input_arr = (long long*) calloc (ARR_SIZE, sizeof(long long));
		func_breaker(input_arr != NULL)
			
		output_arr = (long long*) calloc (ARR_SIZE, sizeof(long long));
		func_breaker(output_arr != NULL)
			
		expect_arr = (long long*) calloc (ARR_SIZE, sizeof(long long));
		func_breaker(expect_arr != NULL)

		long long pow10 = power (10, i    );
		long long base  = power (10, i - 1);
		for (int k = 0; k < ARR_SIZE; ++k) {
			input_arr [k] = (base + k) % pow10;
			expect_arr[k] = (base + k) % pow10;
		}

		shuffle_array (input_arr, ARR_SIZE, 100);

		
		for(int k = 0; k < 2; ++k) {
			copy_array (input_arr, output_arr, ARR_SIZE);
				
			clock_t start = clock();
			char* alg_name[] = {"radix sort", "C++ sort"};
			char* curr_alg = NULL;

			if(k == 0) {
				radix_sort (output_arr, ARR_SIZE);

				curr_alg = alg_name[0];
			}

			else {
				std::sort(output_arr, output_arr + ARR_SIZE);

				curr_alg = alg_name[1];
			}

			work_time [k * DIGIT_LEN + i - START_DIGIT] = clock() - start;
			
			if(cmp_array (expect_arr, output_arr, ARR_SIZE)) {
				printf ("Chaos: 100 %%, digits: %d, sort: %s, res: ok.\n", i, curr_alg);
				printf ("Time: %llu.\n", work_time [k * DIGIT_LEN + i - START_DIGIT]);	
				++count;
			}

			else {
				printf ("Chaos: 100 %%, digits: %d, sort: radix, res: fail.\n", i); 
			}
		}

		free(input_arr );
		free(output_arr);
		free(expect_arr);
	}
			
	if(count == 2 * DIGIT_LEN) {

		printf ("-----------------------\n");
		file = fopen ("digits_dep.txt", "w");

		func_breaker(file != NULL)

		for (int n = 0; n < 2; ++n) {
			for (int m = 0; m < DIGIT_LEN; ++m) {
				fprintf (file, "%llu ", work_time[n * DIGIT_LEN + m]);
			}

			fprintf (file, "\n");
		}

		fclose(file);
	}

	free(work_time);

	//------------------------------------------------------------------------------------------------------

	//iterations for getting data, how speeds depend on array size and randomness
	char* file_name[] = {"20.txt", "40.txt", "60.txt", "80.txt", "100.txt"};
	
	int zero_cnt = 0, file_cnt = 0;

	work_time = (unsigned long long*) calloc (2 * 6, sizeof(unsigned long long));
	func_breaker(work_time != NULL)

	for (int i = 20; i <= 100; i += 20) {
		
		count    = 0;
		zero_cnt = 0;
		
		for (int j = 10; j <= 1000000; j *= 10) {
			
			input_arr = (long long*) calloc (j, sizeof(long long));
			func_breaker(input_arr != NULL)
			
			output_arr = (long long*) calloc (j, sizeof(long long));
			func_breaker(output_arr != NULL)
			
			expect_arr = (long long*) calloc (j, sizeof(long long));
			func_breaker(expect_arr != NULL)

			for (int k = 0; k < j; ++k) {
				input_arr [k] = k;
				expect_arr[k] = k;
			}

			shuffle_array (input_arr, j, i);

			for (int k = 0; k < 2; ++k) {
				
				copy_array (input_arr, output_arr, j);
				
				clock_t start = clock();
				char* alg_name[] = {"radix sort", "C++ sort"}; 
				char* curr_alg = NULL;

				if(k == 0) {
					radix_sort (output_arr, j);

					curr_alg = alg_name[0];
				}

				else {
					std::sort(output_arr, output_arr + j);

					curr_alg = alg_name[1];
				}

				work_time [k * 6 + zero_cnt] = clock() - start;


				if(cmp_array (expect_arr, output_arr, j)) {
					printf ("Chaos: %d %%, size: %d, sort: %s, res: ok.\n", i, j, curr_alg);
					printf ("Time: %llu.\n", work_time [6 * k + zero_cnt]);	
					++count;
				}

				else {
					printf ("Chaos: %d %%, size: %d, sort: %s, res: fail.\n", i, j, curr_alg); 
				}

			}

			++zero_cnt;

			free(input_arr );
			free(output_arr);
			free(expect_arr);
			
		}
			
		
		if(count == 12) {

			printf ("-----------------------\n");
			file = fopen (file_name[file_cnt], "w");

			func_breaker(file != NULL)

			for (int n = 0; n < 2; ++n) {
				for (int m = 0; m < 6; ++m) {
					fprintf (file, "%llu ", work_time[n * 6 + m]);
				}

				fprintf (file, "\n");
			}

			fclose(file);
		}

		++file_cnt;
	}

	free(work_time);


	return 0;

}
