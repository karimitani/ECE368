typedef struct treeNode{
	struct treeNode * right;
	struct treeNode * left;
	double height;
	double width;
	double x_coord;
	double y_coord;
	int label;
	char cutline;
}treeNode;

typedef struct Stack{
	treeNode ** stk;
	int top;
	int size;
}Stack;

void printTreeNode(treeNode *);
void printPostorder(treeNode *);
void savePostOrderHelper(treeNode *, FILE *);
int checkCutline(treeNode *);
void savePostOrder(treeNode *, char *);
int exists(const char *);
Stack * createStack(int);
int countlines(char *);
int isEmpty(Stack *);
void push(Stack *, treeNode *);
treeNode * createNodeCutline(char);
treeNode * createTree(char *);
double max(double, double);
treeNode * findMaxNode (treeNode *, treeNode *);
treeNode * createNodeBox(int, double, double);
void resetCutlines(treeNode *);
void calcXY(treeNode *);
void calcXYhelper(treeNode *, treeNode *);
void destroyTree(treeNode *);
void checkInputs(treeNode *, int *);
void reroot(treeNode *, treeNode *, treeNode *, double *, double *, double *);
int NodeLR(treeNode *, treeNode *);