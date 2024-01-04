#ifndef ANALYZE_H
#define ANALYZE_H

#define SIZE_START 512
#define ITERATION 10
#define ITERATION_SEARCH 10000
#define nano 1E9

// algorithm_t defines different algorithms
typedef enum {
	bubble_sort_t,
	insertion_sort_t,
	quick_sort_t,
	linear_search_t,
	binary_search_t
} algorithm_t;

// case_t defines different cases
typedef enum {
	best_t,
	worst_t,
	average_t,
} case_t;

// arr_t defines different array types
typedef enum {
	random_t,
	sorted_t,
	reverse_t,
} arr_t;

// result_t defines a timed measurement for a given array size
typedef struct {
	int size;
	double time;
} result_t;

typedef enum {
	logn,
	n1,
	nlog,
    nlogn,
    n2, 
    n3,
    t1,
    n2_2,
} output_t;

// benchmark benchmarks an algorithm a for specific case c, writing n results
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n);
int * sortedArr(int * arr, int len);
int * randomArr(int * arr, int len);
int * reverseArr(int * arr, int len);
void timer_sort(int *arr, int len, const algorithm_t a, const case_t c, result_t * buf, int n, int j);
void timer_search(int *arr, int len, const algorithm_t a, const case_t c, result_t * buf, int n, int j);
const char* getAlgorithm(const algorithm_t a);
const char* getCase(const case_t c);
void print_data(int size, double t1, double t2, double t3, double t4);
#endif
