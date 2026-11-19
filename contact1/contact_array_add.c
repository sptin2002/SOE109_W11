#include <stdio.h>
#include <string.h>
#include "contact.h"

char name[51]; // Array to hold the contact name, allowing for 50 characters plus null terminator

contact dataEntry(){
    contact newContact;

    printf("Enter Contact Name: ");
    if(fgets(newContact.name, sizeof(newContact.name), stdin) != NULL){
        // Remove the newline character if present
        newContact.name[strcspn(newContact.name, "\n")] = '\0';
    } else {
        printf("Error reading name input.\n");
        newContact.name[0] = '\0'; // Set to empty string on error
    }

    printf("Enter Contact Phone Number: ");
    if(fgets(newContact.phone, sizeof(newContact.phone), stdin) != NULL){
        // Remove the newline character if present
        newContact.phone[strcspn(newContact.phone, "\n")] = '\0';
    } else {
        printf("Error reading phone input.\n");
        newContact.phone[0] = '\0'; // Set to empty string on error
    }

    return newContact;
}

int addContact(char *filename, contact *contacts){
    FILE *fptr;
    contact newContact = dataEntry();

    fptr = fopen(filename, "ab"); // Open the file in append binary mode
    if(fptr == NULL){
        printf("Error opening file for writing!\n");
        return 1;
    }

    fwrite(&newContact, sizeof(contact),1, fptr); // Write the new contact to the file
    fclose(fptr);

    return 0;
}