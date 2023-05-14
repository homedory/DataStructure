#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet{
	int size;
	int *ptr_arr;
} DisjointSets;

typedef struct _PrintDisjointSet{
	int size;
	int *ptr_arr;
} PrintDisjointSets;

void init(DisjointSets *sets, PrintDisjointSets* maze, int n);
int find(DisjointSets *sets, int x);
void union_(DisjointSets *sets, int i, int j);
void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n);
void printMaze(PrintDisjointSets *maze, int n);
void freeMaze(DisjointSets *sets, PrintDisjointSets *maze);

int main(int argc, char* argv[]) {
	int num;
	FILE *fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &num);
	fclose(fi);

	DisjointSets *sets;
	PrintDisjointSets *maze;

	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze = (PrintDisjointSets*)malloc(sizeof(PrintDisjointSets));

	init(sets, maze, num);

	createMaze(sets, maze, num);

	printMaze(maze, num);
	
	freeMaze(sets, maze);

	return 0;
}

void init(DisjointSets *sets, PrintDisjointSets *maze, int n) {
	sets->size = n * n + 1;
	sets->ptr_arr = (int*)malloc(sets->size * sizeof(int));
	for(int i = 1; i <= n; i++) {
		sets->ptr_arr[i] = -1;
	}

	maze->size = 2 * n * (n+1);
	maze->ptr_arr = (int*)malloc(maze->size * sizeof(int));
	for (int i = 0; i < maze->size; i++) {
		maze->ptr_arr[i] = 1;
	}
	maze->ptr_arr[n] = 0;
	maze->ptr_arr[maze->size - n - 1] = 0;
}

int find(DisjointSets *sets, int x) {
	if(sets->ptr_arr[x] <= 0) {
		return x;
	}
	else {
		return sets->ptr_arr[x] = find(sets, sets->ptr_arr[x]);
	}
}

void union_(DisjointSets *sets, int i, int j) {
	if(sets->ptr_arr[i] < sets->ptr_arr[j]) {
		sets->ptr_arr[j] = i;
	} else if(sets->ptr_arr[i] > sets->ptr_arr[j]) {
		sets->ptr_arr[i] = j;
	} else {
		sets->ptr_arr[j] = i;
		sets->ptr_arr[i]--;
	}
}

void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n) {
	int wall, cell1, cell2, i, j;
	srand(time(NULL));
	while(find(sets, 1) != find(sets, n * n)) {
		wall = rand() % (maze->size);
		if(maze->ptr_arr[wall] == 0 || wall < n || wall >= n * (2*n+1) || wall % (2*n+1) == n || wall % (2*n+1) == 2 * n) 
			continue;
		if(wall % (2*n+1) < n) {
			cell1 = (wall / (n+n+1) - 1) * n + wall % (n+n+1) + 1;
			cell2 = cell1 + n;
		}
		else {
			cell1 = wall / (n+n+1) * n + wall % (n+n+1) - n;
			cell2 = cell1 + 1;
		}
		i = find(sets, cell1);
		j = find(sets, cell2);
		if(i != j) {
			union_(sets, i, j);
			maze->ptr_arr[wall] = 0;
		}
	}
}

void printMaze(PrintDisjointSets *maze, int n) {
	for (int i = 0; i < maze->size; i++) {
		if(i % (n+n+1) < n) {
			if(maze->ptr_arr[i]) 
				printf(" -");
			else 
				printf("  ");
		}
		else {
			if(maze->ptr_arr[i])
				printf("| ");
			else
				printf("  ");
		}
		if(i % (n+n+1) == n - 1 || i % (n+n+1) == 2 * n) 
			printf("\n");
	}
}

void freeMaze(DisjointSets *sets, PrintDisjointSets *maze) {
	free(sets->ptr_arr);
	free(maze->ptr_arr);
	free(sets);
	free(maze);
}
		
