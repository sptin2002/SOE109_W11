#include <stdio.h>

int main() {
    FILE *fptr;
    char c;

    fptr = fopen("INPUT.txt", "w");
    if(fptr == NULL){
        printf("Error opening file!\n");
        return 1;
    }
    printf("Input a sentence: ");
    while((c=getchar()) != '\n'){
        fputc(c, fptr);
    }
    fclose(fptr);

    printf("Sentence written to INPUT file: ");
    fptr = fopen("INPUT.txt", "r");
    if(fptr == NULL){
        printf("Error opening file!\n");
        return 1;
    }
    while((c=fgetc(fptr)) != EOF){
        printf("%c", c);
    }
    fclose(fptr);

    return 0;
}