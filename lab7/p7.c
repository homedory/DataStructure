#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode {
	ElementType Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
}AVLNode;

int Max(ElementType num1, ElementType num2);
int Height(Position P);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
AVLTree Insert(ElementType X, AVLTree T);
void PrintInorder(AVLTree T);
void DeleteTree(AVLTree T);


int Max(ElementType num1, ElementType num2) {
	return num1 > num2 ? num1 : num2;
}

int Height(Position P) {
	if(P == NULL) 
		return -1;
	return P->Height;
}

Position SingleRotateWithLeft(Position node) {
	Position LeftNode = node->Left;
	node->Left = LeftNode->Right;
	LeftNode->Right = node;

	node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
	LeftNode->Height = Max(Height(LeftNode->Left), Height(LeftNode->Right)) + 1;
	return LeftNode;
}

Position SingleRotateWithRight(Position node) {
	Position RightNode = node->Right;
	node->Right = RightNode->Left;
	RightNode->Left = node;

	node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
	RightNode->Height = Max(Height(RightNode->Left), Height(RightNode->Right)) + 1;
	return RightNode;
}

Position DoubleRotateWithLeft(Position node) {
	node->Left = SingleRotateWithRight(node->Left);
	return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node) {
	node->Right = SingleRotateWithLeft(node->Right);
	return SingleRotateWithRight(node);
}

AVLTree Insert(ElementType X, AVLTree T) {
	if(T == NULL) {
		T = (AVLTree) malloc(sizeof(AVLNode));
		T->Left = NULL;
		T->Right = NULL;
		T->Element = X;
		T->Height = 0;
	}
	else if(X < T->Element) {
		T->Left = Insert(X, T->Left);
		if(Height(T->Left) - Height(T->Right) == 2) {
			if(X < T->Left->Element) 
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if(X > T->Element) {
		T->Right = Insert(X, T->Right);
		if(Height(T->Right) - Height(T->Left) == 2) {
			if(X > T->Right->Element)
				T = SingleRotateWithRight(T);
			else 
				T = DoubleRotateWithRight(T);
		}
	}
	else {
		printf("Insertion Error: %d already in the tree!\n", X);
		return T;
	}
	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

void PrintInorder(AVLTree T) {
	if(T == NULL) return;
	PrintInorder(T->Left);
	printf("%d(%d) ", T->Element, T->Height);
	PrintInorder(T->Right);
}

void DeleteTree(AVLTree T) {
	if(T->Left != NULL) 
		DeleteTree(T->Left);
	if(T->Right != NULL)
		DeleteTree(T->Right);
	free(T);
}



int main(int argc, char **argv)
{
	AVLTree myTree = NULL;
	int key;
	FILE *fi = fopen(argv[1], "r");
	while(fscanf(fi, "%d", &key) != EOF) {
		myTree = Insert(key, myTree);
		PrintInorder(myTree);
		printf("\n");
	}
	fclose(fi);
	DeleteTree(myTree);
	return 0;
}
