#include "algorithm.h"

int partition(int v[], int a, int b) {
  int pivot, lower, upper, temp;
  pivot = v[a];
  lower = a + 1;
  upper = b;
  do {
    while (v[lower] <= pivot && lower <= upper) lower = lower + 1;
    while (v[upper] > pivot && lower <= upper) upper = upper - 1;
    if (lower <= upper) {
      temp = v[lower];
      v[lower] = v[upper];
      v[upper] = temp;
      lower = lower + 1;
      upper = upper - 1;
    }
  } while (lower <= upper);
  temp = v[upper];
  v[upper] = v[a];
  v[a] = temp;
  return upper;
}

void quickSort(int v[], int low, int high) 
{
    int p;
        if (low < high) {
            p = partition(v, low, high);
            quickSort(v, low, p-1);
            quickSort(v, p+1, high);
        }
}

void bubble_sort(int *a, int n)
{
    bool has_swapped;    
    do{      
        has_swapped = false;      
        for(int i = 0; i<n -1; i++)
        {        
            if(a[i] > a[i+1])
            {     
                int tmp = a[i];            
                a[i] = a[i+1];           
                a[i+1] = tmp; 
                has_swapped = true;    

            }    
      }   
     }while(has_swapped);
}

void insertion_sort(int *a, int n)
{
 int i, key, j;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

void quick_sort(int *a, int n)
{
    int low = 0;
	  quickSort(a, low, n-1);
}

bool linear_search(const int *a, int n, int v)
{
    for (int i = 0; i < n; i++){
        if(a[i] == v){
            return true;
        }
    }
	return false;
}

bool binary_search(const int *a, int n, int v)
{   int low = 0, high = n-1;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (a[mid] == v)
          return true;

        if (a[mid] < v)
         low = mid + 1;

        else
         high = mid - 1;
  }
	return false;
}
