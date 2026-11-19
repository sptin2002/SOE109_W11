#include <stdio.h>
#include "contact.h"

int getItem(contact *contacts, int recordCount){
    char nameToDelete[51];

    printf("Enter the name to delete: ");
    if(fgets(nameToDelete, sizeof(nameToDelete), stdin) != NULL){
        // Remove the newline character if present
        nameToDelete[strcspn(nameToDelete, "\n")] = '\0';
    } else {
        printf("Error reading name input.\n");
        return -1; // Indicate an error
    }

    for(int i=0; i<recordCount; i++){
        if(strcmp(contacts[i].name, nameToDelete) == 0){
            return i;
        }
    }

    return -1;
}

int deleteContact(char *filename, contact *contacts, int recordCount){
    int indexToDelete = getItem(contacts, recordCount);
    if(indexToDelete == -1){
        printf("Contact not found.\n");
        return -1;
    }

    for(int i=indexToDelete; i<recordCount; i++){
        contacts[i] = contacts[i+1];
    }

    FILE *fptr = fopen(filename, "wb");
    fwrite(contacts, sizeof(contact), recordCount-1, fptr);
    fclose(fptr);
    return 0;
}