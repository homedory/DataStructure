#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct* Heap;
struct HeapStruct
{
	int capacity;
	int size;
	int *elements;
}HeapStruct;

Heap CreateHeap(int heapSize);
void Insert(Heap heap, int value);
int Find(Heap heap, int value);
void DeleteMax(Heap heap);
void PrintHeap(Heap heap);
void FreeHeap(Heap heap);

Heap CreateHeap(int heapSize) {
	Heap heap = (Heap) malloc(sizeof(HeapStruct));
	heap->capacity = heapSize;
	heap->size = 0;
	heap->elements = (int*) malloc((heapSize + 1) * sizeof(int));
	heap->elements[0] = 2147483647;
	return heap;
}

void Insert(Heap heap, int value) {
	if(heap->size == heap->capacity) {
		printf("Insertion Error: Max Heap is full.\n");
		return;
	}
	if(Find(heap, value)) {
		printf("%d is already in the heap.\n", value);
		return;
	}
	printf("Insert %d\n", value);
	int i;
	for(i = ++heap->size; heap->elements[i/ 2] < value; i /= 2) {
		heap->elements[i] = heap->elements[i/2];
	}
	heap->elements[i] = value;
}

int Find(Heap heap, int value) {
	for(int i = 1; i <= heap->size; i++) {
		if(heap->elements[i] == value) {
			return 1;
		}
	}
	return 0;
}

void DeleteMax(Heap heap) {
	if(heap->size == 0) {
		printf("Deletion Error: Max Heap is empty!\n");
		return;
	}
	printf("Max element(%d) deleted.\n", heap->elements[1]);
	int i, Child;
	int LastElement = heap->elements[heap->size--];
	for (i = 1; i * 2<= heap->size; i = Child) {
		Child = i * 2;
		if(Child != heap->size && heap->elements[Child + 1] > heap->elements[Child])
			Child++;
		if(LastElement < heap->elements[Child]) 
			heap->elements[i] = heap->elements[Child];
		else
			break;
	}
	heap->elements[i] = LastElement;
}

void PrintHeap(Heap heap) {
	if(heap->size == 0) {
		printf("Max heap is empty!\n");
		return;
	}
	for(int i = 1; i <= heap->size; i++) {
		printf("%d ", heap->elements[i]);
	}
	printf("\n");
}

void FreeHeap(Heap heap) {
	free(heap->elements);
	free(heap);
}

void main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	char cv;
	Heap maxHeap;
	int value, maxValue;

	while(!feof(fi))
	{
		fscanf(fi, "%c", &cv);	
		switch(cv) {
		case 'n':
			fscanf(fi,"%d", &value);
			maxHeap = CreateHeap(value);
			break;
		case 'i':
			fscanf(fi,"%d", &value);
			Insert(maxHeap, value);
			break;
		case 'd':
			DeleteMax(maxHeap);
			break;
		case 'f':
			fscanf(fi, "%d", &value);
			if(Find(maxHeap, value))
				printf("%d is in the heap.\n", value);
			else
				printf("%d is not in the heap.\n", value);
			break;
		case 'p':
			PrintHeap(maxHeap);
		}
	}
	FreeHeap(maxHeap);
	fclose(fi);
}

