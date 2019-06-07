typedef struct treeNode{
	struct treeNode * left;
	struct treeNode * right;
	double x_coord;
	double y_coord;
	double width;
	double height;
	char cutline;
	int label;
}treeNode;

typedef struct Stack{
	treeNode ** stk;
	int top;
	int size;
}Stack;

int isEmpty(Stack *);
void printTreeNode(treeNode *);
void printPostorder(treeNode *);
void savePostOrderHelper(treeNode *, FILE *);
int checkCutline(treeNode *);
Stack * createStack(int);
int countlines(char *);
void savePostOrder(treeNode *, char *);
int exists(const char *);
void push(Stack *, treeNode *);
treeNode * createTree(char *);
double max(double, double);
treeNode * findMaxNode (treeNode *, treeNode *);
treeNode * createNodeBox(int, double, double);
treeNode * createNodeCutline(char);
void calcXYhelper(treeNode *);
void calcXY(treeNode *, double *, double *);
void destroyTree(treeNode *);
void checkInputs(treeNode *, int *);