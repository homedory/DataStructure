#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct QuickSort{
	int Capacity;
	int Size;
	int* array;
};

typedef struct QuickSort* QuickSort;

QuickSort make_list(int size);
void Insert(QuickSort q, int a);
void printArray(QuickSort q);
void swap(int* a, int* b);
int middle_partition(QuickSort q, int low, int high);
int leftmost_partition(QuickSort q, int left, int right);
int rightmost_partition(QuickSort q, int left, int right);
void quicksort(QuickSort q, int left, int right, int type);

void main(int argc, char* argv[]) {
	char type_s[10];
	int list_size, key, type_i;
	QuickSort q;
	FILE *fi = fopen(argv[1], "r");

	fscanf(fi, "%s", type_s);

	if(!(strcmp(type_s, "leftmost"))) type_i = 0;
	else if(!(strcmp(type_s, "rightmost"))) type_i = 1;
	else if(!(strcmp(type_s, "middle"))) type_i = 2;
	
	fscanf(fi, "%d", &list_size);
	q = make_list(list_size);
	for(int i = 0; i < list_size; i++) {
		fscanf(fi, "%d", &key);
		Insert(q, key);
	}
	quicksort(q, 0, list_size - 1, type_i);

	free(q->array);
	free(q);
}

QuickSort make_list(int size) {
	QuickSort q = (QuickSort)malloc(sizeof(QuickSort));
	q->Capacity = size;
	q->Size = 0;
	q->array = (int*)malloc(size * sizeof(int));

	return q;
}

void Insert(QuickSort q, int a) {
	q->array[q->Size++] = a;
}

void printArray(QuickSort q) {
	printf("result : ");
	for(int i = 0; i < q->Capacity; i++) {
		printf("%d ", q->array[i]);
	}
	printf("\n");
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int middle_partition(QuickSort q, int low, int high) {
	int i = low;
	int j = high;
	int pivot = (low + high) / 2;	
	printf("pivot value : %d\n", q->array[pivot]);
	int pivot_value = q->array[pivot];

	while(1) {
		while(i <= high && q->array[i] < pivot_value) {
			i++;
		}
		while(j >= low && q->array[j] > pivot_value) {
			j--;
		}
		if(i < j) {
			swap(&q->array[i], &q->array[j]);
			if(q->array[i] < pivot_value) 
				i++;
			if(q->array[j] > pivot_value)
				j--;
		}
		else {
			return i;
		}
	}
	/*	
	Fail	
	while(1) {
		while(i < high && q->array[++i] < pivot_value);
		while(j > low && q->array[--j] > pivot_value);
		if(i <= j) {
			swap(&q->array[i], &q->array[j]);
		}
		else {
			return i;
		}
	}
	*/
	/*
	Fail
	while(1) {
		while(i < high && q->array[++i] <= pivot_value);
		while(j > low && q->array[--j] >= pivot_value);
		if(i < j) {
			swap(&q->array[i], &q->array[j]);
		} 
		else {
			if(pivot < j) {
				swap(&q->array[i], &q->array[pivot]);
				return i;
			}
			else if(pivot > i) {
				swap(&q->array[j], &q->array[pivot]);
				return j;
			}
			return pivot;
		}
	}
	*/
	/*	
	int i = low - 1;
	int j = high + 1;
	int pivot = (low + high) / 2;
	swap(&q->array[high], &q->array[pivot]);
	pivot = high;
	printf("pivot value : %d\n", q->array[pivot]);
	int pivot_value = q->array[pivot];
	while(1) {
		while(i < high && q->array[++i] <= pivot_value);
		while(j > low && q->array[--j] >= pivot_value);
		if(i < j) {
			swap(&q->array[i], &q->array[j]);
		} 
		else {
			swap(&q->array[i], &q->array[pivot]);
			return i;
		}
	}
	*/
	
}	

int leftmost_partition(QuickSort q, int left, int right) {
	int i = left;
	int j = right + 1;
	int pivot = left;
	printf("pivot value : %d\n", q->array[pivot]);
	while(1) {
		while(i < right && q->array[++i] <= q->array[pivot]);
		while(j > left && q->array[--j] >= q->array[pivot]);
		if(i < j) swap(&q->array[i], &q->array[j]);
		else {
			swap(&q->array[j], &q->array[pivot]);
			return j;
		}
	}
}

int rightmost_partition(QuickSort q, int left, int right) {
	int i = left - 1;
	int j = right;
	int pivot = right;
	int pivot_value = q->array[pivot];
	printf("pivot value : %d\n", q->array[pivot]);
	while(1) {
		while(i < right && q->array[++i] <= pivot_value);
		while(j > left && q->array[--j] >= pivot_value);
		if(i < j) swap(&q->array[i], &q->array[j]);
		else {
			swap(&q->array[i], &q->array[pivot]);
			return i;
		}
	}
}

void quicksort(QuickSort q, int left, int right, int type) {
	if(left >= right) return;	
	int pivot;
	if(type == 0) {
		pivot = leftmost_partition(q, left, right); 
	}
	else if(type == 1) {
		pivot = rightmost_partition(q, left, right);
	}
	else if(type == 2) {
		pivot = middle_partition(q, left, right);
	}
	printArray(q);
	quicksort(q, left, pivot - 1, type);
	quicksort(q, pivot + 1, right, type);
}

