#include <stdio.h>
#include <string.h>
#include "contact.h"

struct contact *getData(){
    struct contact *item;

    item = (struct contact *)malloc(sizeof(struct contact));
    if(item == NULL){
        return NULL;
    }
    item->next = NULL;

    printf("Enter contact name: ");
    if(fgets(item->name, sizeof(item->name), stdin) != NULL){
        item->name[strcspn(item->name, "\n")] = '\0';
    } else {
        printf("Error reading contact name!");
        item->name[0] = '\0';
    }

    printf("\nEnter contact phone: ");
    if(fgets(item->phone, sizeof(item->phone), stdin) != NULL){
        item->phone[strcspn(item->phone,"\n")] = '\0';
    } else {
        printf("Error reading contact phone!");
        item->phone[0] = '\0';
    }

    return item;
}

int addContact(struct contact *data){
    struct contact *item = getData();
    if(item == NULL){
        printf("Failed getting contact information");
        return 1;
    }

    while(data->next != NULL){
        data = data->next;
    }
    data->next = item;

    return 0;
}