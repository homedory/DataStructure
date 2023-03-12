#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int numbersOfName = atoi(argv[1]);
	char** nameArr = (char**)malloc(numbersOfName * (sizeof(char*)));
	for (int i = 0; i < numbersOfName; i++) {
		nameArr[i] = (char*)malloc(sizeof(char));
	}
	printf("enter %d names:\n", numbersOfName);
	
	for (int i = 0; i < numbersOfName; i++) {
		scanf("%s", nameArr[i]);
	}
	printf("the names you entered:\n");
	for (int i = 0; i < numbersOfName; i++) {
		printf("%s\n", nameArr[i]);
	}

	for (int i = 0; i < numbersOfName; i++) {
		free(nameArr[i]);
	}
	free(nameArr);
}
