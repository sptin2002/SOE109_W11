#include <stdio.h>
#include "contact.h"
void viewContact(struct contact *data){
    printf("%52s   %16s\n", "Contact Name", "Contact Phone");
    while(data->next != NULL){
        data = data->next;
        printf("%52s   %16s\n", data->name, data->phone);
    }
}