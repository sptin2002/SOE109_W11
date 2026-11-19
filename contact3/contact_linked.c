#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact{
    char name[20];
    char phone[14];
    struct contact *next;
};

void clear_input_buffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void wait_for_enter(){
    printf("\nPress Enter to continue...");
    clear_input_buffer();
}

void clearScreen(){
    printf("\033[H\033[J");
    fflush(stdout);
}

void display_menu(){
    printf("\nMain Menu:\n");
    printf("1. Add Contact\n");
    printf("2. View Contacts\n");
    printf("3. Delete Contact\n");
    printf("4. Exit\n\n");
    printf("Please select an option: ");
}

struct contact *loadData(char *filename){
    FILE *fptr = fopen(filename, "rb");
    if(fptr == NULL){
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    struct contact *head = NULL, *tail = NULL;
    struct contact *data = (struct contact *)malloc(sizeof(struct contact));
    if(data == NULL){
        printf("Memory allocation failed\n");
        fclose(fptr);
        return NULL;
    }

    while(fread(data, sizeof(struct contact), 1, fptr) == 1){
        if(head == NULL){
            head = data;
        } else {
            tail->next = data;
        }
        tail = data;
        tail->next = NULL;

        data = (struct contact *)malloc(sizeof(struct contact));
        if(data == NULL){
            printf("Memory allocation failed\n");
            fclose(fptr);
            return NULL;
        }
    }
    free(data);
    fclose(fptr);

    return head;
}

struct contact *addContact(struct contact *head){
    struct contact *newContact = (struct contact *)malloc(sizeof(struct contact));
    if(newContact == NULL){
        printf("Memory allocation failed\n");
        return head;
    }

    printf("Add New Contact\n\n");
    printf("Enter name: ");
    if(fgets(newContact->name, sizeof(newContact->name), stdin) != NULL){
        newContact->name[strcspn(newContact->name, "\n")] = '\0';
    } else {
        printf("Error reading name\n");
        free(newContact);
        return head;
    }

    printf("Enter phone number: ");
    if(fgets(newContact->phone, sizeof(newContact->phone), stdin) != NULL){
        newContact->phone[strcspn(newContact->phone, "\n")] = '\0';
    } else {
        printf("Error reading phone number\n");
        free(newContact);
        return head;
    }

    newContact->next = NULL;

    if(head == NULL){
        head = newContact;
    } else {
        struct contact *temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newContact;
    }

    return head;
}

void viewData(struct contact *head){
    if(head == NULL){
        printf("No contacts available.\n");
        return;
    }

    while(head != NULL){
        printf("Name: %s, Phone: %s\n", head->name, head->phone);
        head = head->next;
    }
}

struct contact *deleteContact(struct contact *head){
    char name[20];
    struct contact *cur, *prev;

    if(head == NULL){
        printf("There is no contact to delete");
        return head;
    }

    printf("Enter the name to be deleted: ");
    if(fgets(name, sizeof(name),stdin) != NULL){
        name[strcspn(name, "\n")] = '\0';
    } else {
        printf("\nNo valid name is entered");
        wait_for_enter();
    }

    prev = NULL;
    cur = head;
    while(cur != NULL && strcmp(cur->name,name) != 0){
        prev = cur;
        cur = cur->next;
    }
    if(cur == NULL){
        printf("Name not found!\n");
        wait_for_enter();
    } else if(prev == NULL){
        head = cur->next;
    } else {
        prev->next = cur->next;
    }
    free(cur);

    return head;
}

void saveData(struct contact *data, char *filename){
    FILE *fptr;
    struct contact *tmp;

    fptr = fopen(filename, "wb");
    while(data != NULL){
        fwrite(data, sizeof(struct contact), 1, fptr);
        tmp = data;
        data = data->next;   
        free(tmp);
    }

    fclose(fptr);
}

int main(){
    int input;
    struct contact *data;
    char filename[100];

    strcpy(filename, "contacts.txt"); // Example filename, you can change it as needed

    data = loadData(filename);

    display_menu();
    while((input = getchar()) != '4'){
        clear_input_buffer();
        clearScreen();
        switch(input){
            case '1':
                data = addContact(data);
                break;
            case '2':
                viewData(data);
                break;
            case '3':
                data = deleteContact(data);
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
        wait_for_enter();
        clearScreen();
        display_menu();
    }
    saveData(data, filename);

    return 0;
}