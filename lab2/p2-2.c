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
	
	int longest_name_len = 0;
	char format[80];

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
		if (longest_name_len < strlen(students[a].name)) 
			longest_name_len = strlen(students[a].name);
		
	}
	sprintf(format,"%%-%ds", longest_name_len); 
	for (int a = 0; a < i; a++) {
		fprintf(fo, format, students[a].name);
		fprintf(fo, " %-10d	%-31s\n", students[a].student_id, students[a].major);
		free(students[a].name);
		free(students[a].major);
	}

	free(students);
}
