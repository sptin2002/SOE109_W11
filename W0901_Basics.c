#include<stdio.h>

int main()
{
FILE *pfile;
char ch = 'A';
long p1, p2;

pfile = fopen("hello.txt","w+");	 

p1 = ftell(pfile);
fputc(ch, pfile);

p2 = ftell(pfile);
printf("1st position %ld\n2nd position %ld\n", p1, p2);

rewind(pfile); 			/*rewind moves the pointer to start of file*/

p1 = ftell(pfile);
ch = fgetc(pfile);

p2 = ftell(pfile);
printf("1st position %ld\n2nd position %ld\n", p1, p2);

printf("ch Contains %c %d\n\n",ch,ch);

fclose(pfile);
return 0;
}

