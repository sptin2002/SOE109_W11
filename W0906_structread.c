#include<stdio.h>
#include<stdlib.h>

struct solar{
	char name[10];
	double diameter;
	int moons;
	double orbit;
	double rotation;
	}planet1, planet2;;

int main(){
FILE *fptro1;

fptro1=fopen("planets2.txt","wb+");

if(fptro1==NULL){
	printf("Cannot open a file\n");
	exit(1);}

gets(planet1.name);
scanf("%lf %d %lf %lf", &planet1.diameter, &planet1.moons, &planet1.orbit, &planet1.rotation);

fwrite(&planet1,sizeof(struct solar),1,fptro1);

rewind(fptro1);

fread(&planet2,sizeof(struct solar),1,fptro1);

printf("%s \n", planet2.name);
printf("%lf \n", planet2.diameter);
printf("%d \n", planet2.moons);
printf("%lf \n", planet2.orbit);
printf("%lf \n", planet2.rotation);

if(fclose(fptro1)!=0)
	printf("Error closing a file\n");

return 0;
}

