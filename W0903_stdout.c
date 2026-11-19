#include<stdio.h>

int main()
{
	char name[50];
	
	fprintf(stdout, "This can be used to print on the screen\n");

	fscanf(stdin, "%s", name);

	fprintf(stdout, "%s\n", name);

    return 0;
}