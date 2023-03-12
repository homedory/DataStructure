#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
	char *name;
	int student_id;
	char *major;
}student;

int main(int argc, char **args)
{
	char *input_path, *output_path;
	FILE *fi, *fo;
	int num;
	int i;

	student* students;
	input_path = args[1];
	output_path = args[2];
	fi = fopen(input_path, "r");
	fo = fopen(output_path, "w");

	fscanf(fi, "%d", &i);
	students = (student*)malloc(i * sizeof(student));
	for (int a = 0; a < i; a++) {
		students[a].name = (char*)malloc(31 * sizeof(char));
		students[a].major = (char*)malloc(31 * sizeof(char));
		fscanf(fi, "%s %d %s", students[a].name, &students[a].student_id, students[a].major);
	}

	for (int a = 0; a < i; a++) {
		fprintf(fo, "%-31s %-15d %-31s\n", students[a].name, students[a].student_id, students[a].major);
		free(students[a].name);
		free(students[a].major);
	}

	free(students);
}
