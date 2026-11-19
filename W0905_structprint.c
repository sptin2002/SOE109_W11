#include<stdio.h>
#include<stdlib.h>

struct solar{
	char name[10];
	double diameter;
	int moons;
	double orbit;
	double rotation;
	}planet1, planet2; 

int main(){
FILE *fptrp, *fptro1;

fptrp=fopen("planets1.txt","r");
fptro1=fopen("out1.txt","w");


if(fptrp==NULL || fptro1==NULL){
	printf("Cannot open a file\n");
	exit(1);}

gets(planet1.name);
scanf("%lf%d%lf%lf", &planet1.diameter, &planet1.moons, &planet1.orbit, &planet1.rotation);			/*read info from user into a structure*/
fprintf(fptro1,"%s %lf %d %lf %lf", planet1.name, planet1.diameter, planet1.moons, planet1.orbit, planet1.rotation);	/*write structure information to a file*/

fscanf(fptrp,"%s %lf %d %lf %lf", planet2.name, &planet2.diameter, &planet2.moons, &planet2.orbit, &planet2.rotation);	/*read from exisitng file into a structure*/
printf("%s %lf %d %lf %lf", planet2.name, planet2.diameter, planet2.moons, planet2.orbit, planet2.rotation);		/*print info on screen*/

if(fclose(fptro1)||fclose(fptrp))
	printf("Error closing a file\n");

return 0;
}

