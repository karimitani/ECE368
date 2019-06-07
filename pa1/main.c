#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include <time.h>

long * subArrayCount (int, int *);
long power(int, int);

int main (int argc, char ** argv) {
	clock_t start_sort;
	clock_t stop_sort;
	clock_t input;
	clock_t output;

	double moves = 0;
	int size = 0;
	long * array;
	double comps = 0;
	int printNum;
	int saveSucc;

	input = clock();
	array = Load_From_File(argv[2], &size);
	start_sort = clock();
	if(argv[1] && (strcmp(argv[1], "i") == 0)) {Shell_Insertion_Sort(array, size, &comps, &moves);}
	else if(argv[1] && (strcmp(argv[1], "s") == 0)) {Shell_Selection_Sort(array, size, &comps, &moves);}
	
	stop_sort = clock();
	printNum = Print_Seq(argv[3], size);
	saveSucc = Save_To_File(argv[4], array, size);
	output = clock();

	double ioTime = (double)((output - input)/CLOCKS_PER_SEC);
	double sortTime = (double)((stop_sort - start_sort)/CLOCKS_PER_SEC);

	printf("\nNumber of long integers read: %d\n", size);
	printf("Number of long integers stored: %d\n", size);
	printf("Length of sequence: %d\n", printNum);
	printf("Number of comparisons: %f\n", comps);
	printf("Number of moves: %f\n", moves);
	printf("I/O time: %f\n", ioTime);
	printf("Sorting time: %f\n", sortTime);
	free(array);
	return 1;
}