#include <stdlib.h>
#include <time.h>
#include "breakers.h"
#include "sort.h"


void shuffle_array (int* array, int size, int shuff_part) {
	
	void_func_breaker(array != NULL)

	void_func_breaker(size > 0)
	void_func_breaker(shuff_part >= 0 && shuff_part <= 100)

	srand(time(NULL));
	int j = 0;

	/*printf("Input array: \n");
	for (int k = 0; k < size; ++k) {
		printf("%d ", array[k]);
	}
	printf("\n");*/

	double tmp = ((double) shuff_part) / 100 * ((double) size);

	int stop = size - ((int) tmp) + 1;

	for (int i = size - 1; i >= stop; --i) {
		j = rand() % (i + 1);
		
		//swap (&array[i], &array[j]);
		int add = array[j];
		array[j] = array[i];
		array[i] = add;
	
		/*printf("Current array (i = %d): \n", i);
		for (int k = 0; k < size; ++k) {
			printf("%d ", array[k]);
		}
		printf("\n");*/
	}

	return;

}

void copy_array (int* src, int* dst, int size) {
	
	void_func_breaker(src != NULL)
	void_func_breaker(dst != NULL)
	
	void_func_breaker(size > 0)

	for (int i = 0; i < size; ++i) {
		dst[i] = src[i];
	}

	return;

}

int cmp_array (int* a, int* b, int size) {
	
	func_breaker(a != NULL)
	func_breaker(b != NULL)
	
	func_breaker(size > 0)

	for (int i = 0; i < size; ++i) {
		if(a[i] != b[i]) {

			printf ("Diff: a[%d] = %d, b[%d] = %d.\n", i, a[i], i, b[i]);
			return 0;
		}
	}

	return 1;

}


int main () {

	int* input_arr  = NULL;
	int* output_arr = NULL;
	int* expect_arr = NULL;

	FILE *file;
	char* file_name[] = {"20.txt", "40.txt", "60.txt", "80.txt", "100.txt"};
	
	int count = 0, zero_cnt = 0, file_cnt = 0;

	unsigned long long TimeValue = 0;
	
	unsigned long long* work_time = calloc (4 * 5, sizeof(unsigned long long));
	func_breaker(work_time != NULL)

	void (*sort_funcs[4]) (int*, int) = {bubble_sort, bubble_sort_check, shaker_sort, comb_sort}; 

	for (int i = 20; i <= 100; i += 20) {
		
		count    = 0;
		zero_cnt = 0;
		
		for (int j = 10; j <= 100000; j *= 10) {
			
			input_arr = calloc (j, sizeof(int));
			func_breaker(input_arr != NULL)
			
			output_arr = calloc (j, sizeof(int));
			func_breaker(output_arr != NULL)
			
			expect_arr = calloc (j, sizeof(int));
			func_breaker(expect_arr != NULL)

			for (int k = 0; k < j; ++k) {
				input_arr [k] = k;
				expect_arr[k] = k;
			}

			shuffle_array (input_arr, j, i);

			for (int k = 0; k < 4; ++k) {
				
				copy_array (input_arr, output_arr, j);
				
				clock_t start = clock();
				sort_funcs[k] (output_arr, j);
				work_time [k * 5 + zero_cnt] = clock() - start;


				if(cmp_array (expect_arr, output_arr, j)) {
					printf ("Chaos: %d %%, size: %d, sort: %d, res: ok.\n", i, j, k);
					printf ("Time: %llu.\n", work_time [5 * k + zero_cnt]);	
					++count;
				}

				else {
					printf ("Chaos: %d %%, size: %d, sort: %d, res: fail.\n", i, j, k); 
				}

			}

			++zero_cnt;

			free(input_arr );
			free(output_arr);
			free(expect_arr);
			
		}
			
		
		if(count == 20) {

			printf ("-----------------------\n");
			file = fopen (file_name[file_cnt], "w");

			func_breaker(file != NULL)

			for (int n = 0; n < 4; ++n) {
				for (int m = 0; m < 5; ++m) {
					fprintf (file, "%llu ", work_time[n * 5 + m]);
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
