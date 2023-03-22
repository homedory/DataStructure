#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* s, int x);
int Pop(Stack* s);
int Top(Stack* s);
void DeleteStack(Stack* s);
int IsEmpty(Stack* s);
int IsFull(Stack* s);
void Postfix(Stack* s, char input_str);

Stack* CreateStack(int max) {
	Stack* s = (Stack*)malloc(sizeof(Stack));
	s->key = (int*)malloc(max * sizeof(int));
	s->top = -1;
	s->max_stack_size = max;
	return s;
}

void Push(Stack* s, int x) {
	if(IsFull(s)) {
		printf("\nError! Your stack is full\n");
		exit(1);
		return;
	}
	else {
		s->key[++s->top] = x;
	}
}

int Pop(Stack* s) {
	if(IsEmpty(s)) {
		printf("\nError! Your stack is empty\n");
		exit(1);
		return 0;
	}
	else {
		return s->key[s->top--];
	}
}

int Top(Stack* s) {
	if(IsEmpty(s)) {
		printf("Your stack is empty");
		return 0;
	}
	else {
		return s->key[s->top];
	}
}

void DeleteStack(Stack* s) {
	free(s->key);
	free(s);
}

int IsEmpty(Stack* s) {
	if(s->top < 0) return 1;
	return 0;
}

int IsFull(Stack* s) {
	if(s->top + 1 == s->max_stack_size) return 1;
	return 0;
}

void Postfix(Stack* s, char input_str) {
	int x = input_str - '0';
	if( x > 0 && x <= 9) {
		Push(s, x);	
	}
	else {
		int a = Pop(s);
		int b = Pop(s);
		int c;
		switch(input_str) {
			case '+':
				c = b + a;
				break;
			case '-':
				c = b - a;
				break;
			case '*':
				c = b * a;
				break;
			case '/':
				c = b / a;
				break;
			case '%':
				c = b % a;
				break;
				
		}
		Push(s, c);
	}	
}


void main(int argc, char* argv[]) 
{
	FILE* fi = fopen(argv[1], "r");

	Stack* stack = CreateStack(10);

	char c;
	printf("Top numbers: ");
	while(1) {
		fscanf(fi, "%c", &c);
		if(c == '#')
			break;

		Postfix(stack, c);
		printf("%d ", Top(stack));
	}

	printf("\n");
	printf("evaluation result: %d\n", Pop(stack));

	fclose(fi);
	DeleteStack(stack);
}
