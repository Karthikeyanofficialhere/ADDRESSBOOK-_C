#ifndef CONTACT_H
#define CONTACT_H
#include<stdbool.h>

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);
bool valid_email_or_not(char * , AddressBook *); 
bool valid_name_or_not(char * , AddressBook *);  
bool valid_phone_or_not(char * , AddressBook *); 

#endif
