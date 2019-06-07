#include <stdio.h>
#include "sorting.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

Node * Load_From_File(char * Filename){
	FILE* f = fopen(Filename, "rb");
	int count = 0; 
	long num;

	if (f == NULL){return NULL;}

	Node * head = 0;
	Node * tail = 0;
	Node * numList = 0;

   	while( fread(&num, sizeof(long), 1, f)) {
		numList = malloc(sizeof(Node));
		if(count != 0) {
			tail->next = numList;  //connect prev node to current node
			numList->value = num;//set new node value
			numList->next = NULL;

			tail = numList;//update tail
  	  	}
		else if(count == 0) {
			numList->value = num;//set new node value
			numList->next = NULL;
			head = numList;
			tail = head;//first node gets created
			count = 1;
		}
	}
   	fclose(f);
	return (head);
}

int Save_To_File(char *Filename, Node * head) {
	FILE* f = fopen(Filename, "wb"); 

	if (f == NULL) {return 0:}
	while (head != NULL){
		fwrite( &(head->value) , sizeof(long), 1, f);
		head = head->next;
  	}
   	fclose(f);
	return (1);
}

long listLen(Node * list) {
	long len = 0;
	while(list != NULL){
		len++;
		list = list->next;
	}
	return len;
}

void printList (Node * list){
		while(list != NULL){
		printf("%lu \n", list->value);
		list=list->next;}
}

Node * reverseList( Node * list) {
	long len = listLen(list);
	if(len == 1) {return list;}

	Node * a = list;
	Node * b = a->next;
	Node * c = b->next;
	a->next = NULL;
	b->next = a;

	while(c != NULL) {
		a = b;
		b = c;
		c = c->next;
		b->next = a;
	}
	return (b);
}

long power(long twos, long threes) {
	int count = 0;
  	long ans = 1;
  	for(count = 0; count < twos; count++) {ans = 2 * ans;}
 	for(count = 0; count < threes; count++) {ans = ans * 3;}
 	return(ans);
}

void Node_destroy(Node * head) {
	if(head == NULL){return;}
	Node * tmp;
	while(head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return;
}

Node * subArrayCount(int Size) {
 	long posn = 0;
 	int row = 0;
 	int element = 0;
 	long val = 0;
 	Node * subArraySeq = 0;
	Node * head = 0;
	Node * tail = 0;

 	for (row = 0; row < Size;row++){ 
     		element = 0;
    	 	while(element <= row){
     			val = power(row - element,element);
     			if (val < Size) {

     	 			subArraySeq = malloc(sizeof(Node));
				if(posn != 0){
					tail->next = subArraySeq;  
					subArraySeq->value = val;
					subArraySeq->next = NULL;

					tail = subArraySeq;//update tail
  	  			}
				else if(posn == 0){
					subArraySeq->value = val;
					subArraySeq->next = NULL;
					head = subArraySeq;
					tail = head;//first node gets created
					posn = 1;

     	 	  		}
			}
     	 		else {
     	 			if(power(row + 1, 0) > Size) {return head;}
        			element = row + 1;
			}  
			element++; 
		}	
	}  
 	return (head);
}

void List_destroy(List * list) {
	List * temp;
	List * temp2;

	if(list == NULL){return;}
	else {
		temp2 = list;
		list = list->next;
		temp2->next = NULL;
	}

	while(list != NULL) {
		temp = list;
		list = list->next;
		free (temp->node);
		free(temp);
	}
	return;
}

Node * insertion_sort(Node * head) {
	if(head->next == NULL) {return head:}
	long len = listLen(head);
	Node * prev = head;
	Node * cur = prev->next;
	Node * nxt = cur->next;
	long j = 0;
	Node * tmp;

	if(prev->value > cur->value) {
		prev->next = nxt;
		cur->next = prev;

		tmp = prev;
		prev = cur;
		cur = tmp;
		head = prev;		
	}

	for(j = 0; j < len-2; j++) {
		if(cur->value > nxt->value) {
			cur->next = nxt->next;
			nxt->next = cur;
			prev->next = nxt;
			
			prev = nxt;
			nxt = cur->next;	
						
		}
		else  {
			prev = prev->next;
			cur = cur->next;
			nxt = nxt->next;
		}
	}	
	return head;
}


Node * Shell_Sort(Node * list)
{
	long len = listLen(list);
	if(len <= 1) {return list:}

	Node * subArrayLens = subArrayCount((int)len);
	subArrayLens = reverseList(subArrayLens);
	Node * subArrayLensHead = subArrayLens;
	List * temp = 0;
	List * shellPntrHead = 0;
	List * shellPntr = 0;
	Node * curNode = 0;
	Node * head = 0;
	long curLen = 0;
	int i = 0;

	while (subArrayLens->next != NULL){
		curLen = subArrayLens->value;
		subArrayLens = subArrayLens->next;

		for(i = 0; i < curLen; i++) {
			shellPntr = malloc(sizeof(List));
			shellPntr->node = NULL;

			if(i == 0){
				shellPntrHead = shellPntr;
				temp = shellPntr;
			}
			else if( i == curLen -1){	
				temp->next = shellPntr;
				shellPntr->next = shellPntrHead;
			}
			else{
				temp->next = shellPntr;
				temp = shellPntr;
			}
		}

		shellPntr = shellPntrHead;
		for(i = 0; i < len; i++) {
			curNode = list;
			list = list->next;
			curNode->next = NULL;	
			Node * xx = shellPntr->node;
			shellPntr->node = curNode;
			curNode->next = xx;
			shellPntr = shellPntr->next;
		}

		shellPntr = shellPntrHead;
		for(i = 0; i < curLen; i++) {
			shellPntr->node = reverseList(shellPntr->node);
			shellPntr = shellPntr->next;
		}

		shellPntr = shellPntrHead; 	
		for(i = 0; i < curLen; i++) {
			Node * x = shellPntr->node;		
			Node * newx = insertion_sort(x);
			shellPntr->node = newx;
			shellPntr = shellPntr->next;
		}

		shellPntr = shellPntrHead; 
		for(i = 0; i < len; i++) {
			curNode = shellPntr->node;
			shellPntr->node = curNode->next;
			curNode->next = NULL;
			
			if(list == NULL) {list = curNode;}
			else {
				curNode->next = list;
				list = curNode;				
			}
			shellPntr = shellPntr->next;			
		}
		list = reverseList(list);
		List_destroy(shellPntrHead);
	}
	head = list;
	head = insertion_sort(list); // for number of shells equal to 1
	Node_destroy(subArrayLensHead);
	return head;
}