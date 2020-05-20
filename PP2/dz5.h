#ifndef _DZ5_H
#define _DZ5_H
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTACT_FIELDS 37

typedef struct {
    char *firstName;
    char *lastName;
    char *displayName;
    char *nickname;
    char *primaryEmail;
    char *secondaryEmail;
    char *screenName;
    char *workPhone;
    char *homePhone;
    char *faxNumber;
    char *pagerNumber;
    char *mobileNumber;
    char *homeAddress;
    char *homeAddress2;
    char *homeCity;
    char *homeState;
    char *homeZipCode;
    char *homeCountry;
    char *workAddress;
    char *workAddress2;
    char *workCity;
    char *workState;
    char *workZipCode;
    char *workCountry;
    char *jobTitle;
    char *department;
    char *organization;
    char *webPage1;
    char *webPage2;
    char *birthYear;
    char *birthMonth;
    char *birthDay;
    char *custom1;
    char *custom2;
    char *custom3;
    char *custom4;
    char *notes;
} Fields;

typedef union {
    Fields named;
    char *array[CONTACT_FIELDS];
} FieldsUnion;

typedef struct node {
    FieldsUnion fields;
    struct node *prev, *next;
} Node;

Node *readContact(FILE *file);
Node *readContacts(FILE *file);
Node *reverseList(Node *list);
void writeToFile(char * fileName, Node *list);
void freeMemory(Node *list);

#endif
