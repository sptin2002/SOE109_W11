#ifndef CONTACT_H
#define CONTACT_H

struct contact{
    char name[51];
    char phone[15];
    struct contact * next;
};
#endif