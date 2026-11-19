#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

char *getName(char *name, size_t size){
    printf("Enter a name to delete: ");
    if(fgets(name, size, stdin) != NULL){
        name[strcspn(name, "\n")] = '\0';
        return name;
    }

    return NULL;
}

int deleteItem(struct contact *data){
    char name[51];
    struct contact *prev, *cur;

    if(getName(name, sizeof(name)) == NULL){
        printf("No target name to delete!\n");
        return 1;
    }
    printf("Name to detele is: %s\n", name);

    if(data->next == NULL){
        printf("No data to delete!\n");
        return 1;
    }

    prev = data;
    cur = data->next;
    while(cur != NULL){
        if(strcmp(cur->name, name) == 0){
            prev->next = cur->next;
            free(cur);

            return 0;
        }
        prev = cur;
        cur = prev->next;
    }

    return 1;
}