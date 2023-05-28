#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue{
	int size;
	int *key;
	int front;
	int rear;
} Queue;

typedef struct _Graph{
	int size;
	int *vertex;
	int **edge;
} Graph;

Queue *CreateQueue(int X);
void Enqueue(Queue *Q, int item);
int Dequeue(Queue *Q);

Graph *CreateGraph(int X);
void InsertEdge(Graph *G, int u, int v);
void Topsort(Graph *G);

int main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	int X, u, v;
	fscanf(fi, "%d", &X);
	Graph *G = CreateGraph(X);
	
	for(int i = 0; i < X; i++) {
		fscanf(fi, "%d", &G->vertex[i]);
	}

	while(fscanf(fi, "%d %d", &u, &v) != EOF) {
		InsertEdge(G, u, v);
	}

	Topsort(G);

	return 0;
}

Queue *CreateQueue(int X) {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->size = 0;
	q->key = (int*)malloc(X * sizeof(int));
	q->front = 0;
	q->rear = -1;

	return q;
}

void Enqueue(Queue *Q, int item) {
	Q->key[++Q->rear] = item;
	Q->size++;
}

int Dequeue(Queue *Q) {
	int temp = Q->key[Q->front++];
	Q->size--;
	return temp;
}

Graph *CreateGraph(int X) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->size = X;
	g->vertex = (int*)malloc(X * sizeof(int));
	g->edge = (int**)malloc(X * sizeof(int*));
	for(int i = 0; i < X; i++) {
		g->edge[i] = (int*)malloc(X * sizeof(int));
	}
	for(int i = 0; i < X; i++) {
		for(int j = 0; j < X; j++) {
			g->edge[i][j] = 0;
		}
	}

	return g;
}

void InsertEdge(Graph *G, int u, int v) {
	int x, y;
	for(int i = 0; i < G->size; i++) {
		if(G->vertex[i] == u) 
			x = i;
		if(G->vertex[i] == v)
			y = i;
	}
	G->edge[x][y] = 1;
}

void Topsort(Graph *G) {
	Queue* Q = CreateQueue(G->size);
	int* in_degree = (int*)malloc(G->size * sizeof(int));
	for(int i = 0; i < G->size; i++) {
		in_degree[i] = 0;
	}
	for(int i = 0; i < G->size; i++) {
		for(int j = 0; j < G->size; j++) {
			if(G->edge[i][j] == 1) {
				in_degree[j] += 1;
			}
		}
	}
	for(int i = 0; i < G->size; i++) {
		if(in_degree[i] == 0) {
			Enqueue(Q, i);
		}
	}
	while(Q->size != 0) {
		int x = Dequeue(Q);
		printf("%d ", G->vertex[x]);
		for(int i = 0; i < G->size; i++) {
			if(G->edge[x][i] == 1) {
				if(in_degree[i] == 1)
					Enqueue(Q, i);
				in_degree[i]--;
			}
		}
	}
	printf("\n");
}

		
