#include <stdio.h>
#include <stdlib.h>

struct MergeSort{
	int Capacity;
	int Size;
	int *array;
	int *Tmparray;
};
typedef struct MergeSort* MergeSort;

MergeSort make_list(int size);
void Insert(MergeSort m, int a);
void printArray(MergeSort A, int l, int r);
void RmergeSort(MergeSort A, int l, int r);
void ImergeSort(MergeSort A, int n);
void merge(MergeSort A, int l ,int m, int r);

int main(int argc, char* argv[]) {
	int size, key;
	int *iter_tmp, *rec_tmp;
	FILE *fi = fopen(argv[1], "r");
	MergeSort iter_m, rec_m;

	fscanf(fi, "%d", &size);

	iter_m = make_list(size);
	rec_m = make_list(size);

	for (int i = 0; i < size; i++) {
		fscanf(fi, "%d", &key);
		Insert(iter_m, key);
		Insert(rec_m, key);
	}

	printf("input : \n");
	printArray(iter_m, 0, iter_m->Size-1);
	printf("\n");

	printf("iterative: \n");
	ImergeSort(iter_m, iter_m->Size-1);
	printf("\n");

	printf("Recursive: \n");
	RmergeSort(rec_m, 0, rec_m->Size-1);
	printf("\n");

}



MergeSort make_list(int size) {
	MergeSort A = (MergeSort)malloc(sizeof(MergeSort));
	A->Capacity = size;
	A->Size = 0;
	A->array = (int*)malloc(size * sizeof(int));
	A->Tmparray = (int*)malloc(size * sizeof(int));

	return A;
}

void Insert(MergeSort m , int a) {
	m->array[m->Size++] = a;
}

void printArray(MergeSort A, int l, int  r) {
	for(int i = l; i <= r; i++) {
		printf("%d ", A->array[i]);
	}
	printf("\n");
}

void RmergeSort(MergeSort A, int l, int r) {
	if(l >= r) return;	
	int mid = (l+r)/2;
	RmergeSort(A, l, mid);
	RmergeSort(A, mid + 1, r);
	merge(A, l, mid, r);
	printArray(A, l, r);
}

void merge(MergeSort A, int l, int m, int r) {
	int tmp = l;
	int lpos = l;
	int rpos = m + 1;
	while(lpos <= m && rpos <= r) {
		if(A->array[lpos] < A->array[rpos]) {
			A->Tmparray[tmp++] = A->array[lpos++];
		}
		else {
			A->Tmparray[tmp++] = A->array[rpos++];
		}
	}
	while(lpos <= m) {
		A->Tmparray[tmp++] = A->array[lpos++];
	}
	while(rpos <= r) {
		A->Tmparray[tmp++] = A->array[rpos++];
	}
	for(int i = l; i <= r; i++) {
		A->array[i] = A->Tmparray[i];
	}
}

void ImergeSort(MergeSort A, int n) {
	for(int i = 2; i <= 2 * n; i *= 2) {
		for(int j = 0; j <= n; j += i) {
			int lend = j + i / 2 - 1;
			int lpos = j;
			int rpos = lend + 1;
			int tmp = j;
			int rend = j + i - 1;
			if(rend > n) {
				rend = n;
				if(lend > n) {
					lend = n;
				}
			}

			while(lpos <= lend && rpos <= rend) {
				if(A->array[lpos] < A->array[rpos]) {
					A->Tmparray[tmp++] = A->array[lpos++];
				}
				else {
					A->Tmparray[tmp++] = A->array[rpos++];
				}
			}
			while(lpos <= lend) {
				A->Tmparray[tmp++] = A->array[lpos++];
			}
			while(rpos <= rend) {
				A->Tmparray[tmp++] = A->array[rpos++];
			}
			for(int k = j; k <= rend; k++) {
				A->array[k] = A->Tmparray[k];	
			}
			printArray(A, j, rend);
		}
	}
}


