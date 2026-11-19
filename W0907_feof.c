#include<stdio.h>

int main()
{
char c;
FILE *p;

p=fopen("hello.txt","wb+");

fprintf(p, "hello");

rewind(p);

while(!feof(p))
	{
	c=fgetc(p);
	printf("%c",c);
	}
	

fclose(p);

return 0;
}

