#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
    char name[20];
    char phone[14];
} contact;

void pause_seconds(int seconds){
    sleep(seconds); // This is a more straightforward way to pause for a specified number of seconds
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
    printf("Menu:\n");
    printf("1. Add Contact\n");
    printf("2. View Contact\n");
    printf("3. Delete Contact\n");
    printf("q. Quit\n");
    printf("Please enter your selection: ");
}

contact *loadData(char *filename, int *recordCount){
    FILE *fptr;
    contact *data;
    long filesize;

    fptr = fopen(filename, "rb");
    if(fptr == NULL){
        printf("Failed opening data file!");
        return NULL;
    }

    fseek(fptr, 0L, SEEK_END);
    filesize = ftell(fptr);
    data = (contact *)malloc(filesize);
    if(data == NULL){
        printf("Memory allocation failed!");
        return NULL;
    }
    *recordCount = (int)(filesize / sizeof(contact));

    rewind(fptr);
    if(fread(data, sizeof(contact), *recordCount, fptr) != *recordCount){
        printf("Problem reading data file. Restart the program and try again!");
        return NULL;
    }

    fclose(fptr);
    return data;
}

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

int addContact(char *filename){
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

void viewContacts(contact *contacts, int recordCount){
    for(int i = 0; i < recordCount; i++){
        printf("Contact %4d:", i + 1);
        printf(" Name: %20s", contacts[i].name);
        printf(" Phone: %14s\n", contacts[i].phone);
    }
}

int getItem(contact *contacts, int recordCount){
    char nameToDelete[20];

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

int main(){
    int selection;
    contact *data;
    char filename[] = "contacts.dat"; // Assuming the data file is named contacts.dat
    int recordCount;

    data = loadData(filename, &recordCount); // Load data from the file (assuming contacts.dat is the data file)

    displayMenu();

    while((selection = getchar()) && (selection != 'q' && selection != 'Q')){
        switch(selection){
            case '1':
                /* call dataEntry function */
                clearInputBuffer();
                if(addContact(filename) == 0){
                    printf("Contact added successfully!\n");
                    data = loadData(filename, &recordCount); // Reload data after adding a contact
                } else {
                    printf("Failed to add contact.\n");
                }
                pause_seconds(2); // Pause for 2 seconds to allow the user to read the message
                // clearInputBuffer(); // Clear the input buffer after reading the selection
                break;
            case '2':
                viewContacts(data, recordCount);
                pause_seconds(5); // Pause for 5 seconds to allow the user to read the
                clearInputBuffer(); // Clear the input buffer after reading the selection
                break;
            case '3':
                clearInputBuffer(); // Clear the input buffer after reading the selection
                if(deleteContact(filename, data, recordCount) == 0){
                    printf("Contact deleted successfully!\n");
                    data = loadData(filename, &recordCount); // Reload data after adding a contact
                } else {
                    printf("Failed to delete contact.\n");
                }
                pause_seconds(2); // Pause for 2 seconds to allow the user to read the message
                break;
            default:
                printf("Invalid selection. Please try again.\n");
                clearInputBuffer(); // Clear the input buffer after reading the selection
        }

        displayMenu();
    }


    return 0;
}