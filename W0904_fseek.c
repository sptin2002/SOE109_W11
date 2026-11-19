#include<stdio.h>

int main()
{
FILE *pfile;		 /*file pointer pfile*/
char ch;
pfile = fopen("alpha.txt","r+");
			
fseek(pfile, 0L, SEEK_END);    	 /*offset is type long*/

printf("Byte count is %ld\n",ftell(pfile));

fseek(pfile, 6L, SEEK_SET);

ch=fgetc(pfile);
printf("The character read was %c\n",ch);
printf("Byte count is %ld\n",ftell(pfile));

fseek(pfile, 0L, SEEK_CUR);

fputc('Z',pfile);

printf("Byte count is %ld\n",ftell(pfile));

fclose(pfile);

return 0;
}

