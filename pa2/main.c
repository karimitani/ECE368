#include <stdio.h>
#include "sorting.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

Node * reverseList( Node *);
void printList (Node *);
long listLen(Node *);
Node * subArrayCount(int);
void appendNode(Node *, Node *);
void List_destroy(List *);
Node * insertion_sort(Node *);
Node * insertNode(Node *, Node *);
void Node_destroy(Node *);

int main (int argc, char ** argv) {
	clock_t io_start;
	clock_t io_end;
	clock_t sort_start;
	clock_t sort_end;
	Node * list;

	// IO clock started
	io_start = clock();
	list = Load_From_File(argv[1]);

	//sorting clock started
	sort_start = clock();
	list = Shell_Sort(list);
	sort_end = clock(); // sorting clock ended

	Save_To_File(argv[2], list);
	io_end = clock(); // IO clock ended

	Node_destroy(list);
	printf("I/O time:  %le seconds\n", (double)(io_end-io_start)/CLOCKS_PER_SEC);
	printf("Sorting time:  %le seconds\n", (double)(sort_end-sort_start)/CLOCKS_PER_SEC);

return EXIT_SUCCESS;
}