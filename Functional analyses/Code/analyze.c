#include "analyze.h"
#include "algorithm.h"

int * sortedArr(int * arr, int len)
{
  for (int i = 0; i < len; i++) 
  {
    arr[i] = i;
  }
  return arr;  
}

int * randomArr(int * arr, int len)
{
  srand(time(NULL));
  for(int i = 0; i < len; i++)
  {
    arr[i] = (rand() % len) + 1;
  }
  return arr;
}

int * reverseArr(int * arr, int len)
{
  for (int i = 0; i < len; i++) 
  {
    arr[i] = len - i;
  }
  return arr;
}

void benchmark(const algorithm_t a, const case_t c, result_t * buf, int n) {
  int * arr, len = 512;
  int j = 0;

  if(a == bubble_sort_t || a == insertion_sort_t || a == quick_sort_t ) {
    for(int i = 0; i < n; i++) {
      arr = (int * ) malloc(len * sizeof(int));
      timer_sort(arr, len, a, c, buf, n, j);
      len *= 2, j++;
    }
  }

  if(a == linear_search_t || a == binary_search_t) {
    for(int i = 0; i < n; i++) {
      arr = (int * ) malloc(len * sizeof(int));
      timer_search(arr, len, a, c, buf, n, j);
      len *= 2, j++;
    }
  }
}

void timer_sort(int *arr, int len, const algorithm_t a, const case_t c, result_t * buf, int n, int j) {
  struct timespec start, stop;
  buf[0].size = SIZE_START;

  for(int k = 0; k < ITERATION; k++) {
    if(c == best_t) sortedArr(arr,len);
    if(c == average_t) randomArr(arr, len);
    if(c == worst_t) reverseArr(arr, len);

    if(a == quick_sort_t && c == best_t) randomArr(arr,len);
    if(a == quick_sort_t && c == worst_t) sortedArr(arr,len);
    if(a == quick_sort_t && c == average_t) randomArr(arr,len);

    clock_gettime(CLOCK_MONOTONIC, & start);
    if(a == bubble_sort_t) bubble_sort(arr, len);
    if(a == quick_sort_t) quick_sort(arr, len);
    if(a == insertion_sort_t) insertion_sort(arr, len);   
    clock_gettime(CLOCK_MONOTONIC, & stop);

    buf[j].time += ((double)(stop.tv_sec * nano + stop.tv_nsec) - (start.tv_sec * nano + start.tv_nsec)) / nano;
  }

  buf[j + 1].size = buf[j].size * 2;
  buf[j].time = buf[j].time / ITERATION;
}

void timer_search(int *arr, int len, const algorithm_t a, const case_t c, result_t * buf, int n, int j) {
  int x;
  struct timespec start, stop;
  buf[0].size = SIZE_START;

  for(int k = 0; k < ITERATION_SEARCH; k++) {
    srand(time(NULL));
    if(a == binary_search_t && c == best_t) x = len/2;
    if(a == binary_search_t && c == worst_t) x = 1;
    if(a == binary_search_t && c == average_t) {
      sortedArr(arr,len);
      x = rand() % len;
    }

    if(c == best_t) sortedArr(arr,len);
    if(c == worst_t) reverseArr(arr, len);

    if(a == linear_search_t && c == best_t) x = 1;
    if(a == linear_search_t && c == worst_t) x = 1;
    if(a == linear_search_t && c == average_t) {
      sortedArr(arr,len);
      x = rand() % len;
    }

    clock_gettime(CLOCK_MONOTONIC, & start);
    if(a == linear_search_t) linear_search(arr, len,x);
    if(a == binary_search_t) binary_search(arr, len,x);    
    clock_gettime(CLOCK_MONOTONIC, & stop);

    buf[j].time += ((double)(stop.tv_sec * nano + stop.tv_nsec) - (start.tv_sec * nano + start.tv_nsec)) / nano;
  }

  buf[j + 1].size = buf[j].size * 2;
  buf[j].time = buf[j].time / ITERATION_SEARCH;
}
