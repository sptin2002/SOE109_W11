#include <stdio.h>
#include "contact.h"

void viewContacts(contact *contacts, int recordCount){
    for(int i = 0; i < recordCount; i++){
        printf("Contact %4d:", i + 1);
        printf(" Name: %52s", contacts[i].name);
        printf(" Phone: %16s\n", contacts[i].phone);
    }
}