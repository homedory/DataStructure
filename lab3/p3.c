#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node {
	ElementType element;
	Position next;
};

List MakeEmptyList();
int isLast(Position p, List l);
void Delelte(ElementType x, List l);
Position FindPrevious(ElementType x, List l); //if there is no key in a list, return last element
Position Find(ElementType x, List l); //if there is no key in a list, return NULL
void insert(ElementType x, Position p, List l);
void DeleteList(List l);
void PrintList(List l);

List MakeEmptyList()
{
	List l = (List)malloc(sizeof(struct Node));
	l->element = -999;
	l->next = NULL;
	return l;
}

int isLast(Position p, List l)
{
	List current = l;
	while(current->next != NULL) {
		current = current->next;
	}

	return p == current;
}

Position FindPrevious(ElementType x, List l)
{
	Position p = l;
	while(p->next != NULL && p->next->element != x) {
		p = p->next;
	}
	return p;
}

Position Find(ElementType x, List l)
{
	if(x == -1) {
		return l;
	}
	Position p = l;
	while(p != NULL && p->element != x) {
		p = p->next;
	}
	return p;
}

void Insert(ElementType x, Position p, List l)
{
	if(p == NULL) {
		printf("Insertion(%d) Failed: cannot find the location to be inserted.\n", x);
		return;
	}
	Position tmp = (Position)malloc(sizeof(Position));
	tmp->element = x;
	tmp->next = p->next;
	p->next = tmp;	
}


void Delete(ElementType x, List l)
{
	Position p = FindPrevious(x, l);
	if(isLast(p, l)) {
		printf("Deletion failed: element %d is not in the list.\n", x);
	}
	else {
		Position tmp = p->next;
		p->next = tmp->next;
		free(tmp);
	}	
}

void DeleteList(List l)
{
	Position tmp, p = l;
	while(p != NULL) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
}

void PrintList(List l)
{
	Position p = l;
	if(p->next == NULL) {
		printf("your list is empty.\n");
		return;
	}
	p = p->next;
	while(p != NULL) {
		printf("key: %d  ", p->element);
		p = p->next;
	}
	printf("\n");
}




int main(int argc, char* argv[])
{
	char command;
	FILE* input, output;
	int key1, key2;
	Position header = NULL, tmp = NULL;

	if(argc <= 1) {
		printf("Please enter input file\n");
		return 0;
	}
	else {
		input = fopen(argv[1], "r");
	}

	header = MakeEmptyList();
	while(1) {
		command = fgetc(input);
		if(feof(input)) break;

		switch(command) {
		case 'i':
			fscanf(input,"%d %d", &key1, &key2);
			tmp = Find(key2, header);
			Insert(key1, tmp, header);

			break;
		case 'd':
			fscanf(input, "%d", &key1);
			Delete(key1, header);

			break;
		case 'f':
			fscanf(input, "%d", &key1);
			tmp = FindPrevious(key1, header);
			if(isLast(tmp, header)) {
				printf("Could not find %d in the list.\n", key1);
			}
			else if(tmp->element > 0) {
				printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
			}
			else {
				printf("key of the previous node of %d is header\n", key1);
			}

			break;
		case 'p':
			PrintList(header);
			break;
		case '\n':
			break;
		default :	
			printf("Invalid command line\n");
		}	
	}
	
	DeleteList(header);
	fclose(input);

	return 0;
}
