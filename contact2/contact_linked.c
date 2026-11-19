#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "contact_linked_add.c"
#include "contact_linked_view.c"
#include "contact_linked_delete.c"
#include "contact.h"

void pause_seconds(int seconds){
    sleep(seconds); // This is a more straightforward way to pause for a specified number of seconds
}

void clearInputBuffer(){
    int ch;

    while((ch = getchar()) != '\n' && ch != EOF);
}

void clearScreen(){
    // Clear the console screen
    // This is platform-dependent; for Windows, use "cls", for Unix/Linux, use "clear"
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayMenu(){
    clearScreen();
    printf("Main Menu\n");
    printf("1. Add Contact\n");
    printf("2. View Contact\n");
    printf("3. Delete Contact\n");
    printf("4. QUIT\n\n");            
    printf("Your Selection: ");
}

struct contact *loadData(char *filename){
    FILE *fptr;
    struct contact *data, *cur;

    fptr = fopen(filename, "rb");
    if(fptr == NULL){
        printf("Failed opening data file");
        return NULL;
    }

    data = cur = (struct contact *)malloc(sizeof(struct contact));
    if(data == NULL){
        return NULL;
    }
    strcpy(cur->name, "");
    strcpy(cur->phone, "");

    cur->next = (struct contact *)malloc(sizeof(struct contact));
    if(cur->next == NULL){
        return NULL;
    }
    while(fread(cur->next, sizeof(struct contact), 1, fptr) == 1){
        cur = cur->next;
        cur->next = (struct contact *)malloc(sizeof(struct contact));
    }
    free(cur->next);
    cur->next = NULL;

    return data;
}

int save(struct contact *data, char *filename){
    FILE *fptr;
    struct contact *temp;

    fptr = fopen(filename, "wb");
    if(fptr == NULL){
        printf("Failed opening destination file. Try again later!");
        return 1;
    }
    while(data->next != NULL){
        fwrite(data->next, sizeof(struct contact), 1, fptr);
        temp = data;
        data = data->next;
        printf("Writing %51s\n", data->name);
        free(temp);
    }
    fclose(fptr);
    return 0;
}

int main(){
    int selection;
    struct contact *data;
    char *filename;

    filename = "contacts.dat";

    data = loadData(filename);
    displayMenu();
    while((selection = getchar()) && selection != 'q' && selection != 'Q'){

        clearInputBuffer();
        switch(selection){
            case '1':
                addContact(data);
                break;
            case '2':
                viewContact(data);
                break;
            case '3':
                deleteItem(data);
                break;
            default:
                printf("Your selection is invalid\n");
        }
        pause_seconds(2);
        displayMenu();
    }

    save(data, filename);
    free(data);

}