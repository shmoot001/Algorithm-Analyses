#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}
  
static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search average case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search average case",
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

const char * getAlgorithm(const algorithm_t a) {
  switch (a) {
  case bubble_sort_t:
    return "Bubble sort";
  case insertion_sort_t:
    return "Insertion sort";
  case quick_sort_t:
    return "Quick sort";
  case linear_search_t:
    return "Linear searcch";
  case binary_search_t:
    return "Binary search";
  }
  return "Unvalid Algo";
}

const char * getCase(const case_t c) {
  switch (c) {
  case best_t:
    return "best";
  case worst_t:
    return "worst";
  case average_t:
    return "average";
  }
  return "Unvalid Case";
}

const char * getOutput(const output_t o) {
  switch (o) {
  case logn:
    return "T/logn";
  case t1: 
	return "T/1";
  case n1:
    return "T/n";
  case nlog:
    return "T/nlog";
  case nlogn:
    return "T/nlogn";
  case n2:
    return "T/n^2";
  case n2_2: 
	return "T/(n/2)";
  case n3:
    return "T/n^3";
  }
  return "Unvalid output";

}

void print_list(const algorithm_t a,const case_t c, const output_t str1, const output_t str2, const output_t str3) {
  ui_line('*', 100);
  printf("\t\t\t\t%s : %s\n", getAlgorithm(a), getCase(c));
  ui_line('~', 100);
  printf("size\ttime T(s)\t\t%s\t\t\t%s\t\t\t%s\t\n", getOutput(str1), getOutput(str2), getOutput(str3));
  ui_line('~', 100);
}

void print_data(int size, double t1, double t2, double t3, double t4) {
  printf("%d \t%e\t\t%e\t\t%e\t\t%e\n", size, t1, t2, t3, t4);
}

void calc(const algorithm_t a, result_t * result){

	if(a == bubble_sort_t || a == insertion_sort_t || a == quick_sort_t)
	{	
		for(int k = 0, len = 512 ; k < RESULT_ROWS; k++, len *= 2) 
		{
			print_data(result[k].size, result[k].time, result[k].time / len * log((double) len), result[k].time / len, result[k].time / (len * len));
		}
	}
	if(a == linear_search_t)
	{	
		for(int k = 0, len = 512 ; k < RESULT_ROWS; k++, len *= 2) 
		{
			print_data(result[k].size, result[k].time, result[k].time / 1, result[k].time / len, result[k].time / (len / 2));
		}
	}
  	if (a == binary_search_t)
	{
		for(int k = 0, len = 512 ; k < RESULT_ROWS; k++, len *= 2) 
		{
			print_data(result[k].size, result[k].time, result[k].time / 1, result[k].time / len, result[k].time / log((double)len));
		}
	}
		
}

void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];
	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;
			case 'b':
				running = false;
				break;
			// Bubble sort
			case 'c':
				print_list(bubble_sort_t,best_t,nlogn,n1,n2);
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				calc(bubble_sort_t,result);
				break;
			case 'd':
				print_list(bubble_sort_t,worst_t,nlogn,n1,n2);
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				calc(bubble_sort_t,result);
				break;
			case 'e':
				print_list(bubble_sort_t,average_t,nlogn,n1,n2);
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				calc(bubble_sort_t,result);
				break;
			case 'f':
				print_list(insertion_sort_t,best_t,nlogn,n1,n2);
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				calc(insertion_sort_t,result);
				break;
			case 'g':
				print_list(insertion_sort_t,worst_t,nlogn,n1,n2);
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
				calc(insertion_sort_t,result);
				break;
			case 'h':
				print_list(insertion_sort_t,average_t,nlogn,n1,n2);
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
				calc(insertion_sort_t,result);
				break;
			case 'i':
				print_list(quick_sort_t,best_t,nlogn,n1,n2);
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				calc(quick_sort_t,result);
				break;
			case 'j':
				print_list(quick_sort_t,worst_t,nlogn,n1,n2);
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
				calc(quick_sort_t,result);
				break;
			case 'k':
				print_list(quick_sort_t,average_t,nlogn,n1,n2);
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
				calc(quick_sort_t,result);
				break;
			case 'l':
				print_list(linear_search_t,best_t,t1,n1,n2_2);
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);
				calc(linear_search_t,result);
				break;
			case 'm':
				print_list(linear_search_t,worst_t,t1,n1,n2_2);
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
				calc(linear_search_t,result);
				break;
			case 'n':
				print_list(linear_search_t,average_t,t1,n1,n2_2);
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);
				calc(linear_search_t,result);
				break;
			case 'o':
				print_list(binary_search_t,best_t,t1,n1,logn);
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);
				calc(binary_search_t,result);
				break;
			case 'p':
				print_list(binary_search_t,worst_t,t1,n1,logn);
				benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
				calc(binary_search_t,result);
				break;
			case 'q':
				print_list(binary_search_t,average_t,t1,n1,logn);
				benchmark(binary_search_t, average_t, result, RESULT_ROWS);
				calc(binary_search_t,result);
				break;
			

			// Invalid input
			default:
				show_menu = false;
				ui_invalid_input();
				break;
		}
	}
	ui_exit();
}
