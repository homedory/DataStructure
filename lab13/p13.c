#include <stdio.h>
#include <stdlib.h>

const int INF = (int)2e9;

typedef struct Node {
	int vertex;
	int dist;
	int prev;
} Node;

typedef struct Graph {
	int size;
	Node* nodes;
	int** matrix;
} Graph;

Graph* createGraph(int X);
Graph* findShortestPath(Graph* G, int s);
void printShortestPath(Graph* G);

typedef struct Heap {
	int capacity;
	int size;
	Node* elements;
} Heap;

Heap* createMinHeap(int X);
void insert(Heap* H, Node N);
Node deleteMin(Heap* H);
void decreaseKey(Heap* H, Node N);

int main(int* argc, char* argv[]) {
	FILE *fi = fopen(argv[1], "r");
	int size;

	fscanf(fi, "%d", &size);
	
	Graph* G = createGraph(size);

	int node_s, node_d, weight;
	while(fscanf(fi, "%d %d %d", &node_s, &node_d, &weight) != EOF) {
		G->matrix[node_s][node_d] = weight;
	}

	G = findShortestPath(G, 1);
	
	printShortestPath(G);

	return 0;
}

Graph* createGraph(int X) {
	Graph* G = (Graph*)malloc(sizeof(Graph));
	G->size = X;
	G->nodes = (Node*)malloc((X+1) * sizeof(Node));
	for(int i = 1; i <= X; i++) {
		G->nodes[i].vertex = i;
		G->nodes[i].dist = INF;
		G->nodes[i].prev = i;
	}
	
	G->matrix = (int**)malloc((X+1) * sizeof(int*));
	for(int i = 0; i < X+1; i++) {
		G->matrix[i] = (int*)malloc((X+1) * sizeof(int));
	}

	return G;
}

Graph* findShortestPath(Graph* G, int s) {
	Heap* Q = createMinHeap(G->size);
	G->nodes[s].dist = 0;
	for(int i = 1; i <= G->size; i++) {
		insert(Q, G->nodes[i]);
	}
	while(Q->size > 0) {
		Node n = deleteMin(Q);
		int u = n.vertex;
		for(int i = 1; i <= G->size; i++) {
			if(G->matrix[u][i] > 0 && G->nodes[i].dist > G->nodes[u].dist + G->matrix[u][i]) {
				G->nodes[i].dist = G->nodes[u].dist + G->matrix[u][i];
				G->nodes[i].prev = u;
				decreaseKey(Q, G->nodes[i]);
			}
		}
	}
	return G;
}

void printShortestPath(Graph* G) {
	for(int i = 2; i <= G->size; i++) {
		printf("%d", i);
		int v = i;
		if(G->nodes[i].dist != INF) {
			while(G->nodes[v].prev != G->nodes[v].vertex) {
				printf("<-%d", G->nodes[v].prev);
				v = G->nodes[v].prev;
			}
			printf(" cost: %d\n", G->nodes[i].dist);
		}
		else {
			printf(" can not be reached.\n");
		}
	}
}

Heap* createMinHeap(int X) {
	Heap* H = (Heap*)malloc(sizeof(Heap));
	H->capacity = X;
	H->size = 0;
	H->elements = (Node*)malloc((X+1) * sizeof(Node));
}

void insert(Heap* H, Node N) {
	int i = ++H->size;
	while(H->elements[i/2].dist > N.dist) {
		H->elements[i] = H->elements[i/2];
		i /= 2;
	}
	H->elements[i] = N;
}

Node deleteMin(Heap* H) {
	int i , child;
	Node n = H->elements[1]; 
	for(i = 1; i * 2 <= H->size; i = child) {
		child = i * 2;
		if(child != H->size && H->elements[child + 1].dist < H->elements[child].dist)
			child++;
		if(H->elements[child].dist < H->elements[H->size].dist)
			H->elements[i] = H->elements[child];
		else
			break;
	}
	H->elements[i] = H->elements[H->size--];
	return n;
}

void decreaseKey(Heap* H, Node N) {
	int v = N.vertex;
	int loc;
	for(int i = 1; i <= H->size; i++) {
		if(H->elements[i].vertex == v) {
			loc = i;
			H->elements[i] = N;
			break;
		}
	}
	while(H->elements[loc/2].dist > H->elements[loc].dist) {
		H->elements[loc] = H->elements[loc/2];
		loc /= 2;
	}
	H->elements[loc] = N;
}

