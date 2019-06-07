#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "packing.h"

void printTreeNode(treeNode * node) {
	printf("label: %d, ", node->label);
	printf("cutline: %c, ", node->cutline);
	printf("width: %le, ", node->width);
	printf("height: %le \n", node->width);
	return;
}

int exists(const char * filename){
    FILE *file;

    if ((file = fopen(filename, "r"))){
        fclose(file);
        return 1;}
    return 0;
}

double max(double x, double y){
	if(x > y){return x;}
	else{return y;}
	return 0;
}

int checkCutline(treeNode * node){
	char cl = node->cutline;
	if(cl == 'H'){return 1;}
	else if(cl == 'V'){return 0;}
	return -1;
}

void printPostorder(treeNode * node){
	if(node == NULL){return;}
	printPostorder(node->left);
	printPostorder(node->right);
	
	if(checkCutline(node) == -1){printf("\n%d width: %le, height: %le, x coord: %le, y coord: %le ", node->label, node->width, node->height, node->x_coord, node->y_coord);}
	else{printf("\n%c width: %le, height: %le, x coord: %le, y coord: %le ", node->cutline, node->width, node->height, node->x_coord, node->y_coord);	}
	return;
}

treeNode * findMaxNode(treeNode * tree, treeNode * lastNode) {
	if(tree == NULL) {return NULL;}
	if(tree->left != NULL) {lastNode = findMaxNode(tree->left, lastNode);}
	if(tree->right != NULL) {lastNode = findMaxNode(tree->right, lastNode);}
	if(tree->label > lastNode->label){lastNode = tree;}
	return lastNode;
}

int countlines(char *filename) {
  	FILE * fp = fopen(filename,"r");
  	char ch = 0;
  	int lines = 0;

  	while (!feof(fp)) {
		ch = fgetc(fp);
      	if (ch == '\n'){lines++;}
    }
  	fclose(fp);
  	return lines;
}

treeNode * createNodeCutline(char cutline) {
	treeNode * newNode = malloc(sizeof(treeNode));
	newNode->cutline = cutline;
	newNode->label = 0;
	newNode->width = 0;
	newNode->height = 0;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->x_coord = 0;
	newNode->y_coord = 0;
	return newNode;
}

treeNode * createNodeBox(int label, double width, double height){
	treeNode * newNode = malloc(sizeof(treeNode));
	newNode->label = label;
	newNode->width = width;
	newNode->height = height;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->x_coord = 0;
	newNode->y_coord = 0;
	newNode->cutline = 0;
	return newNode;
}

void savePostOrderHelper(treeNode * node, FILE * ptr) {
	if(node->left != NULL){savePostOrderHelper(node->left, ptr);}	
	if(node->right != NULL){savePostOrderHelper(node->right, ptr);}	
	if(checkCutline(node) == -1){fprintf(ptr, "%d %le %le %le %le\n", node->label, node->width, node->height, node->x_coord, node->y_coord);}
	return;
}

void savePostOrder(treeNode * node, char * filename){
	if(node == NULL){return;}

	FILE * 	ptr = fopen(filename, "w");
	savePostOrderHelper(node, ptr);
	fclose(ptr);

	return;
}

void destroyTree(treeNode * root){
	if(root == NULL){return;}

	treeNode * rootRight = root->right;
	treeNode * rootLeft = root->left;
	destroyTree(rootLeft);
	destroyTree(rootRight);

	free (root);
	return;
}

void checkInputs(treeNode * root, int * err){
	if(root == NULL){return;}

	treeNode * rootRight = root->right;
	treeNode * rootLeft = root->left;
	checkInputs(rootLeft, err);
	checkInputs(rootRight, err);

	if(checkCutline(root) > -1){if((rootRight == NULL) || (rootLeft == NULL)){*err = *err + 1;}}
	if(checkCutline(root) == -1) {if((rootRight != NULL) || (rootLeft != NULL)){*err = *err + 1;}}

}
 
Stack * createStack(int size){
	Stack * stack = malloc(sizeof(Stack));
	stack->size = size;
	stack->top = -1;
	stack->stk = malloc(sizeof(treeNode) * size);
	return stack;
}

void push(Stack * stack, treeNode * node){
	if(stack->top == stack->size - 1){return;}
	else {
		stack->top = stack->top + 1;
		stack->stk[stack->top] = node;
	}
	return;
}

int isEmpty(Stack * stack){
	if(stack->top == -1){return 1;}
	else{return 0;}
}

treeNode * pop(Stack * stack){
	if(isEmpty(stack)){return NULL;}
	else{stack->top = stack->top - 1;}
	return (stack->stk[stack->top + 1]);
}

treeNode * createTree(char * filename){
	int label = 0;
	double width = 0;
	double height = 0;
	char cutline = 0;
	treeNode * newNode = NULL;
	int i;

	//if filename is NULL
	if(filename == NULL){return newNode;}

	//create stack
	int fileLen = countlines(filename);
	Stack * stack = createStack(fileLen);

	//use stack to make tree
	FILE * ptr = fopen(filename, "r");
	for(i = 0; i < fileLen; i++){
		if(fscanf(ptr, "%d(%le, %le)\n", &label, &width, &height) == 3){
			newNode = createNodeBox (label, width, height);
			push(stack, newNode);
		}
		else if(fscanf(ptr, "%c\n", &cutline) == 1){
			newNode = createNodeCutline (cutline);
			newNode->right = pop(stack);
			newNode->left = pop(stack);
			push(stack, newNode);
		}
	}
	
	stack->top = stack->top - 1;
	while(!isEmpty(stack)){
		free(stack->stk[stack->top]);
		stack->top = stack->top - 1;
	}

	free(stack->stk);
	free(stack);

	fclose(ptr);
	return newNode;
}

void calcXY(treeNode * root){

	treeNode * rootLeft = root->left;
	treeNode * rootRight = root->right;

	if(rootLeft == NULL && rootRight == NULL) {return;}

	if(checkCutline(root) == 1) {
		calcXY(rootRight);
		calcXY(rootLeft);
		root->width = max(rootLeft->width, rootRight->width);
		root->height = rootLeft->height + rootRight->height;
		root->y_coord = rootRight->height;
		calcXYhelper(root, rootLeft);

	}
	else if(checkCutline(root) == 0) {
		calcXY(rootLeft);
		calcXY(rootRight);
		root->width = rootLeft->width + rootRight->width;
		root->height = max(rootLeft->height, rootRight->height);
		root->x_coord = rootLeft->width;
		calcXYhelper(root, rootRight);

	}
	return;
}

void calcXYhelper(treeNode * root, treeNode * child){
	if(child == NULL){return;}

	child->x_coord = child->x_coord + root->x_coord;
	child->y_coord = child->y_coord + root->y_coord;
	calcXYhelper(root, child->left);
	calcXYhelper(root, child->right);
	
	return;
}	

void resetCutlines(treeNode * root){
	if(root == NULL) {return;}

	resetCutlines(root->left);
	resetCutlines(root->right);

	if(checkCutline(root) == 0 || checkCutline(root) == 1){
		root->height = 0;
		root->width = 0;

	}
	return;
}

int NodeLR(treeNode * parent, treeNode * child) {
	if(parent->left == child) {return 1;}
	else if(parent->right == child) {return 0;}
	return -1; // 'child' is not a child of 'parent'
}


void reroot(treeNode * root, treeNode * parent, treeNode * curNode, double * minH, double * minW, double * minA) {
	if(parent == NULL || root == NULL || curNode == NULL) {return;}
	if(curNode->left == NULL || curNode->right == NULL){return;}

	//Declarations
	int LR = NodeLR(parent, curNode); // if LR is 1 child is on the left of parent. If 0, child is on the right of parent.
	treeNode * temp;
	
	//left reroot
	temp = curNode->right;
	curNode->right = root;
	if(LR == 1) {parent->left = temp;}
	else if(LR == 0) {parent->right = temp;}

	//calc area
	resetCutlines(curNode);
	calcXY(curNode);
	if(curNode->width * curNode->height < * minA) {
		* minA = curNode->width * curNode->height;
		* minH = curNode->height;
		* minW = curNode->width;
	}
	else if((curNode->width * curNode->height == * minA) && (curNode->width < * minW)){
		* minA = curNode->width * curNode->height;
		* minH = curNode->height;
		* minW = curNode->width;	
	}

	//recursive call
	reroot(curNode, curNode, curNode->left, minH, minW, minA);

	//undoing the reroot
	curNode->right = temp;
	if(LR == 1) {parent->left = curNode;}
	else if(LR == 0) {parent->right = curNode;}	

	//right reroot
	temp = curNode->left;
	curNode->left = root;
	if(LR == 1) {parent->left = temp;}
	else if(LR == 0) {parent->right = temp;}

	//calc area
	resetCutlines(curNode);
	calcXY(curNode);
	if(curNode->width * curNode->height < * minA) {
		* minA = curNode->width * curNode->height;
		* minH = curNode->height;
		* minW = curNode->width;
	}
	else if((curNode->width * curNode->height == * minA) && (curNode->width < * minW)) {
		* minA = curNode->width * curNode->height;
		* minH = curNode->height;
		* minW = curNode->width;	
	}
	
	//recursive call
	reroot(curNode, curNode, curNode->right, minH, minW, minA);	
	
	//undoing the reroot
	curNode->left = temp;
	if(LR == 1) {parent->left = curNode;}
	else if(LR == 0) {parent->right = curNode;}
	return;
}	