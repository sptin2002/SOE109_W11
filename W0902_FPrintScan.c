#include<stdio.h>

int main()
{
FILE *pfile;/*file pointer pfile*/
char text[20];

pfile = fopen("hello.txt","w+");		/*new file for r&w*/

fprintf(pfile, "HELLO");

printf("%ld",ftell(pfile));

rewind(pfile); 		/*rewind moves the pointer to*/

fscanf(pfile, "%s", text);		/* the start of the file*/

printf("%s\n", text);

return 0;
}

