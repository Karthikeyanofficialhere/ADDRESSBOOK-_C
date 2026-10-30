#include "contact.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

void initialize(AddressBook *addressBook)  // loading contacts to structure
{
    int i = 0;
    addressBook->contactCount = 0;
    FILE *fptr = fopen("contacts.txt", "r");
    while(fscanf(fptr, " %[^,],%[^,],%[^\n]", addressBook->contacts[i].name, 
                addressBook->contacts[i].phone, addressBook->contacts[i].email) > 0)
    {
        addressBook->contactCount++;
        i++;
    }
    fclose(fptr);
}
void listContacts(AddressBook *addressBook)  // displaying contacts in structure
{
    int i;
    printf("---------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-20s | %-30s |\n", "S.NO", "NAME", "PHONE", "E-MAIL");
    printf("---------------------------------------------------------------------------------------------\n");
    for(i = 0; i < addressBook->contactCount; i++)
    {
        printf("! %-10d | %-20s | %-20s | %-30s |", i + 1, 
            addressBook->contacts[i].name, 
            addressBook->contacts[i].phone, 
            addressBook->contacts[i].email);
        printf("\n");
    }
    printf("---------------------------------------------------------------------------------------------\n");
}
void saveAndExit(AddressBook *addressBook)  // saving to file and terminating program
{
    int i;
    FILE *fptr = fopen("contacts.txt", "w");
    for(i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", 
            addressBook->contacts[i].name, 
            addressBook->contacts[i].phone, 
            addressBook->contacts[i].email);
    }
    fclose(fptr);
    exit (0);
}
void createContact(AddressBook *addressBook) // creating new contact
{
    if(addressBook->contactCount < 100)
    {
        int flag = 0, count = 0;
        char temp_storage[50] = {0}, temp_storage1[50] = {0}, temp_storage2[50] = {0};
        while(count <= 3 && flag != 1)
        {
            printf("Enter the Name : ");
            scanf(" %[^\n]", temp_storage);
            if(valid_name_or_not(temp_storage, addressBook))
            {
                strcpy(addressBook->contacts[addressBook->contactCount].name, temp_storage);
                flag = 1;
            }
            else
            {
                count++;
                if(count == 3)
                {
                    printf("\033[1;91m-----------------------------\n");
                    printf("| MAXIMUM ATTEMPTS REACHED! |\n");
                    printf("-----------------------------\033[0m\n");
                    return;
                }
            }
        }
        flag = 0, count = 0;
        while(count <= 3 && flag != 1)
        {
            printf("Enter the Phone No : ");
            scanf(" %[^\n]", temp_storage1);
            if(valid_phone_or_not(temp_storage1, addressBook))  // validate and check the phone no already available
            {
                strcpy(addressBook->contacts[addressBook->contactCount].phone, temp_storage1);
                flag = 1;
            }
            else
            {
                count++;
                if(count == 3)
                {
                    printf("\033[1;91m-----------------------------\n");
                    printf("| MAXIMUM ATTEMPTS REACHED! |\n");
                    printf("-----------------------------\033[0m\n");
                    return;
                }
            }
        }
        flag = 0, count = 0;
        while(count <= 3 && flag != 1)
        {
            printf("Enter the E-MAIL : ");
            scanf(" %[^\n]", temp_storage2);
            if(valid_email_or_not(temp_storage2, addressBook))  // validate and check the e-mail already available
            {
                strcpy(addressBook->contacts[addressBook->contactCount].email, temp_storage2);
                flag = 1;
            }
            else
            {
                count++;
                if(count == 3)
                {
                    printf("\033[1;91m-----------------------------\n");
                    printf("| MAXIMUM ATTEMPTS REACHED! |\n");
                    printf("-----------------------------\033[0m\n");
                    return;
                }
            }
        }
        addressBook->contactCount++;
        printf("\033[1;92m--------------------------------\n");
        printf("| Contact Created successfully |\n");
        printf("--------------------------------\033[0m\n");
    }
    else
    {
        printf("\033[1;91mMAXIMUM CONTACTS REACHED\033[0m\n");
    }
}
void searchContact(AddressBook *addressBook)    // searching for a contact
{
    while(1)
    {
        char keyword[50];
        int count = 0, i, indices[100] = {0}, m = 0, n = 1, max = 0;
        printf("Enter something to search contact : ");
        scanf(" %[^\n]", keyword);
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].name, keyword) != NULL || 
                    strcasestr(addressBook->contacts[i].phone, keyword) != NULL || 
                    strcasestr(addressBook->contacts[i].email, keyword) != NULL)
            {
                count++;
            }
        }
        if(count > 0)
        {
            printf("---------------------------------------------------------------------------------------------\n");
            printf("| %-10s | %-20s | %-20s | %-30s |\n", "S.NO", "NAME", "PHONE", "E-MAIL");
            printf("---------------------------------------------------------------------------------------------\n");
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strcasestr(addressBook->contacts[i].name, keyword) != NULL || 
                        strcasestr(addressBook->contacts[i].phone, keyword) != NULL || 
                        strcasestr(addressBook->contacts[i].email, keyword) != NULL)
                {
                    if(strcasestr(addressBook->contacts[i].name, keyword) != NULL)
                    {
                        int j, k, count1 = 0, size = strlen(keyword);
                        printf("| %-10d | ", n);
                        for(j = 0; addressBook->contacts[i].name[j] != '\0'; j++)
                        {
                            if(count1 < size && strchr(keyword, addressBook->contacts[i].name[j]) != NULL)
                            {
                                printf("\033[1;93m%c\033[0m", addressBook->contacts[i].name[j]);
                                count1++;
                            }
                            else
                            {
                                printf("%c", addressBook->contacts[i].name[j]);
                            }
                        }
                        for(k = 0; k <= 20 - j; k++)
                        {
                            printf(" ");
                        }
                    }
                    else
                    {
                        printf("| %-10d | %-20s ", n, addressBook->contacts[i].name);
                    }
                    if(strcasestr(addressBook->contacts[i].phone, keyword) != NULL)
                    {
                        int j, k, count1 = 0, size = strlen(keyword);
                        printf("| ");
                        for(j = 0; addressBook->contacts[i].phone[j] != '\0'; j++)
                        {
                            if(count1 < size && strchr(keyword, addressBook->contacts[i].phone[j]) != NULL)
                            {
                                printf("\033[1;93m%c\033[0m", addressBook->contacts[i].phone[j]);
                                count1++;
                            }
                            else
                            {
                                printf("%c", addressBook->contacts[i].phone[j]);
                            }
                        }
                        for(k = 0; k <= 20 - j; k++)
                        {
                            printf(" ");
                        }
                    }
                    else
                    {
                        printf("| %-20s ", addressBook->contacts[i].phone);
                    }
                    if(strcasestr(addressBook->contacts[i].email, keyword) != NULL)
                    {
                        int j, k, count1 = 0, size = strlen(keyword);
                        printf("| ");
                        for(j = 0; addressBook->contacts[i].email[j] != '\0'; j++)
                        {
                            if(count1 < size && strchr(keyword, addressBook->contacts[i].email[j]) != NULL)
                            {
                                printf("\033[1;93m%c\033[0m", addressBook->contacts[i].email[j]);
                                count1++;
                            }
                            else
                            {
                                printf("%c", addressBook->contacts[i].email[j]);
                            }
                        }
                        for(k = 0; k < 30 - j; k++)
                        {
                            printf(" ");
                        }
                        printf(" |\n");
                    }
                    else
                    {
                        printf("| %-30s |\n", addressBook->contacts[i].email);
                    }
                    indices[m++] = i;
                    n++;
                    if(i > max)
                    {
                        max = i;
                    }
                }
            }
            printf("---------------------------------------------------------------------------------------------\n");
        }
        if(m > 0)
        {
            while(1)
            {
                int choice;
                printf("Enter the serial number of the contact you want : ");
                scanf("%d", &choice);
                if(choice <= max)
                {
                    printf("\033[1;92m-----------------------------------------\n");
                    printf("Name : %s\n", addressBook->contacts[indices[choice - 1]].name);
                    printf("phone : %s\n", addressBook->contacts[indices[choice - 1]].phone);
                    printf("E-MAIL : %s\n", addressBook->contacts[indices[choice - 1]].email);
                    printf("------------------------------------------\033[0m\n");
                    return;
                }
                else
                {
                    printf("\033[1;91m-------------------------\n");
                    printf("| Enter a valid choice! |\n");
                    printf("-------------------------\033[0m\n");
                }
            }
        }
        else
        {
            printf("\033[1;91m----------------------------------------\n");
            printf("| Keyword not found enter a valid one! |\n");
            printf("----------------------------------------\033[0m\n");
        }
    }
}
void editContact(AddressBook *addressBook)   // editing the contact by contact details
{
    while(1)
    {
        char keyword[50];
        int count = 0, i, indices[100] = {0}, m = 0, n = 1, max = 0;
        printf("Enter something to search contact : ");
        scanf(" %[^\n]", keyword);
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].name, keyword) != NULL || 
                    strcasestr(addressBook->contacts[i].phone, keyword) != NULL || 
                    strcasestr(addressBook->contacts[i].email, keyword) != NULL)
            {
                count++;
            }
        }
        if(count > 0)
        {
            printf("---------------------------------------------------------------------------------------------\n");
            printf("| %-10s | %-20s | %-20s | %-30s |\n", "S.NO", "NAME", "PHONE", "E-MAIL");
            printf("---------------------------------------------------------------------------------------------\n");
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strcasestr(addressBook->contacts[i].name, keyword) != NULL || 
                        strcasestr(addressBook->contacts[i].phone, keyword) != NULL || 
                        strcasestr(addressBook->contacts[i].email, keyword) != NULL)
                {
                    if(strcasestr(addressBook->contacts[i].name, keyword) != NULL)
                    {
                        int j, k, count1 = 0, size = strlen(keyword);
                        printf("| %-10d | ", n);
                        for(j = 0; addressBook->contacts[i].name[j] != '\0'; j++)
                        {
                            if(count1 < size && strchr(keyword, addressBook->contacts[i].name[j]) != NULL)
                            {
                                printf("\033[1;93m%c\033[0m", addressBook->contacts[i].name[j]);
                                count1++;
                            }
                            else
                            {
                                printf("%c", addressBook->contacts[i].name[j]);
                            }
                        }
                        for(k = 0; k <= 20 - j; k++)
                        {
                            printf(" ");
                        }
                    }
                    else
                    {
                        printf("| %-10d | %-20s ", n, addressBook->contacts[i].name);
                    }
                    if(strcasestr(addressBook->contacts[i].phone, keyword) != NULL)
                    {
                        int j, k, count1 = 0, size = strlen(keyword);
                        printf("| ");
                        for(j = 0; addressBook->contacts[i].phone[j] != '\0'; j++)
                        {
                            if(count1 < size && strchr(keyword, addressBook->contacts[i].phone[j]) != NULL)
                            {
                                printf("\033[1;93m%c\033[0m", addressBook->contacts[i].phone[j]);
                                count1++;
                            }
                            else
                            {
                                printf("%c", addressBook->contacts[i].phone[j]);
                            }
                        }
                        for(k = 0; k <= 20 - j; k++)
                        {
                            printf(" ");
                        }
                    }
                    else
                    {
                        printf("| %-20s ", addressBook->contacts[i].phone);
                    }
                    if(strcasestr(addressBook->contacts[i].email, keyword) != NULL)
                    {
                        int j, k, count1 = 0, size = strlen(keyword);
                        printf("| ");
                        for(j = 0; addressBook->contacts[i].email[j] != '\0'; j++)
                        {
                            if(count1 < size && strchr(keyword, addressBook->contacts[i].email[j]) != NULL)
                            {
                                printf("\033[1;93m%c\033[0m", addressBook->contacts[i].email[j]);
                                count1++;
                            }
                            else
                            {
                                printf("%c", addressBook->contacts[i].email[j]);
                            }
                        }
                        for(k = 0; k < 30 - j; k++)
                        {
                            printf(" ");
                        }
                        printf(" |\n");
                    }
                    else
                    {
                        printf("| %-30s |\n", addressBook->contacts[i].email);
                    }
                    indices[m++] = i;
                    n++;
                    if(i > max)
                    {
                        max = i;
                    }
                }
            }
            printf("---------------------------------------------------------------------------------------------\n");
        }
        if(m > 0)
        {
            while(1)
            {
                int choice;
                printf("Enter the serial number of the contact to be edited : ");
                scanf("%d", &choice);
                if(choice <= max)
                {
                    while(1)
                    {
                        int count = 0;
                        char option;
                        printf("-----------------\n");
                        printf("|1. Edit name   |\n");
                        printf("|2. Edit phone  |\n");
                        printf("|3. Edit email  |\n");
                        printf("|4. Back        |\n");
                        printf("-----------------\n");
                        printf("Enter the option you want to edit : ");
                        scanf(" %c", &option);
                        switch (option)
                        {
                            case '1':
                                while(count <= 2)
                                {
                                    char new_name[50];
                                    printf("Enter new name : ");
                                    scanf(" %[^\n]", new_name);
                                    if(valid_name_or_not(new_name, addressBook) == 1)
                                    {
                                        strcpy(addressBook->contacts[indices[choice - 1]].name, new_name);
                                        printf("\033[1;92m------------------------------\n");
                                        printf("| Name changed successfully! |\n");
                                        printf("------------------------------\033[0m\n");
                                        break;
                                    }
                                    else
                                    {
                                        count++;
                                        if(count == 3)
                                        {
                                            printf("\033[1;91m-----------------------------\n");
                                            printf("| MAXIMUM ATTEMPTS REACHED! |\n");
                                            printf("-----------------------------\033[0m\n");
                                            return;
                                        }
                                    }
                                }
                                break;
                            case '2':
                                while(1)
                                {
                                    char new_phone[20];
                                    printf("Enter new phone no : ");
                                    scanf(" %[^\n]", new_phone);
                                    if(valid_phone_or_not(new_phone, addressBook) == 1)
                                    {
                                        strcpy(addressBook->contacts[indices[choice - 1]].phone, new_phone);
                                        printf("\033[1;92m--------------------------------------\n");
                                        printf("| Phone number changed successfully! |\n");
                                        printf("--------------------------------------\033[0m\n");
                                        break;
                                    }
                                    else
                                    {
                                        count++;
                                        if(count == 3)
                                        {
                                            printf("\033[1;91m-----------------------------\n");
                                            printf("| MAXIMUM ATTEMPTS REACHED! |\n");
                                            printf("-----------------------------\033[0m\n");
                                            return;
                                        }
                                    }
                                }
                                break;
                            case '3':
                                while(1)
                                {
                                    char new_email[20];
                                    printf("Enter new E-MAIL id : ");
                                    scanf(" %[^\n]", new_email);
                                    if(valid_email_or_not(new_email, addressBook) == 1)
                                    {
                                        strcpy(addressBook->contacts[indices[choice - 1]].email, new_email);
                                        printf("\033[1;92m--------------------------------\n");
                                        printf("| E-MAIL changed successfully! |\n");
                                        printf("--------------------------------\033[0m\n");
                                        break;
                                    }
                                    else
                                    {
                                        count++;
                                        if(count == 3)
                                        {
                                            printf("\033[1;91m-----------------------------\n");
                                            printf("| MAXIMUM ATTEMPTS REACHED! |\n");
                                            printf("-----------------------------\033[0m\n");
                                            return;
                                        }
                                    }
                                }
                                break;
                            case '4':
                                return;
                            default:
                                break;
                        }
                        char ch;
                        printf("do you want to edit anything in the same contact (y/n) : ");
                        scanf(" %c", &ch);
                        if(ch == 'n')
                        {
                            return;
                        }
                    }
                }
                else
                {
                    printf("\033[1;91m-------------------------\n");
                    printf("| Enter a valid choice! |\n");
                    printf("-------------------------\033[0m\n");
                }
            }
        }
        else
        {
            printf("\033[1;91m----------------------------------------\n");
            printf("| Keyword not found enter a valid one! |\n");
            printf("----------------------------------------\033[0m\n");
        }
    }
}
void deleteContact(AddressBook *addressBook)  // deleting a whole contact
{
    while(1)
    {
        char keyword[50];
        int count = 0, i, indices[100] = {0}, m = 0, n = 1, max = 0;
        printf("Enter something to search contact : ");
        scanf(" %[^\n]", keyword);
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].name, keyword) != NULL || 
                    strcasestr(addressBook->contacts[i].phone, keyword) != NULL || 
                    strcasestr(addressBook->contacts[i].email, keyword) != NULL)
            {
                count++;
            }
        }
        if(count > 0)
        {
            printf("---------------------------------------------------------------------------------------------\n");
            printf("| %-10s | %-20s | %-20s | %-30s |\n", "S.NO", "NAME", "PHONE", "E-MAIL");
            printf("---------------------------------------------------------------------------------------------\n");
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strcasestr(addressBook->contacts[i].name, keyword) != NULL || 
                        strcasestr(addressBook->contacts[i].phone, keyword) != NULL || 
                        strcasestr(addressBook->contacts[i].email, keyword) != NULL)
                {
                    if(strcasestr(addressBook->contacts[i].name, keyword) != NULL)
                    {
                        int j, k, count1 = 0, size = strlen(keyword);
                        printf("| %-10d | ", n);
                        for(j = 0; addressBook->contacts[i].name[j] != '\0'; j++)
                        {
                            if(count1 < size && strchr(keyword, addressBook->contacts[i].name[j]) != NULL)
                            {
                                printf("\033[1;93m%c\033[0m", addressBook->contacts[i].name[j]);
                                count1++;
                            }
                            else
                            {
                                printf("%c", addressBook->contacts[i].name[j]);
                            }
                        }
                        for(k = 0; k <= 20 - j; k++)
                        {
                            printf(" ");
                        }
                    }
                    else
                    {
                        printf("| %-10d | %-20s ", n, addressBook->contacts[i].name);
                    }
                    if(strcasestr(addressBook->contacts[i].phone, keyword) != NULL)
                    {
                        int j, k, count1 = 0, size = strlen(keyword);
                        printf("| ");
                        for(j = 0; addressBook->contacts[i].phone[j] != '\0'; j++)
                        {
                            if(count1 < size && strchr(keyword, addressBook->contacts[i].phone[j]) != NULL)
                            {
                                printf("\033[1;93m%c\033[0m", addressBook->contacts[i].phone[j]);
                                count1++;
                            }
                            else
                            {
                                printf("%c", addressBook->contacts[i].phone[j]);
                            }
                        }
                        for(k = 0; k <= 20 - j; k++)
                        {
                            printf(" ");
                        }
                    }
                    else
                    {
                        printf("| %-20s ", addressBook->contacts[i].phone);
                    }
                    if(strcasestr(addressBook->contacts[i].email, keyword) != NULL)
                    {
                        int j, k, count1 = 0, size = strlen(keyword);
                        printf("| ");
                        for(j = 0; addressBook->contacts[i].email[j] != '\0'; j++)
                        {
                            if(count1 < size && strchr(keyword, addressBook->contacts[i].email[j]) != NULL)
                            {
                                printf("\033[1;93m%c\033[0m", addressBook->contacts[i].email[j]);
                                count1++;
                            }
                            else
                            {
                                printf("%c", addressBook->contacts[i].email[j]);
                            }
                        }
                        for(k = 0; k < 30 - j; k++)
                        {
                            printf(" ");
                        }
                        printf(" |\n");
                    }
                    else
                    {
                        printf("| %-30s |\n", addressBook->contacts[i].email);
                    }
                    indices[m++] = i;
                    n++;
                    if(i > max)
                    {
                        max = i;
                    }
                }
            }
            printf("---------------------------------------------------------------------------------------------\n");
        }
        if(m > 0)
        {
            while(1)
            {
                int choice;
                printf("Enter the serial number of the contact to be deleted : ");
                scanf("%d", &choice);
                if(choice <= max)
                {
                    char yes_no;
                    printf("Are you sure you want to delete (y/n) : ");
                    scanf(" %c", &yes_no);
                    if(yes_no == 'y')
                    {
                        for(i = indices[choice - 1]; i < addressBook->contactCount - 1; i++)
                        {
                            strcpy(addressBook->contacts[i].name, addressBook->contacts[i + 1].name);
                            strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);
                            strcpy(addressBook->contacts[i].email, addressBook->contacts[i + 1].email);
                        }
                        addressBook->contactCount--;
                        printf("\033[1;92m---------------------------------\n");
                        printf("| contact deleted successfully! |\n");
                        printf("---------------------------------\033[0m\n");
                        return;
                    }
                    else
                    {
                        return;
                    }
                }
                else
                {
                    printf("\033[1;91m-------------------------\n");
                    printf("| Enter a valid choice! |\n");
                    printf("-------------------------\033[0m\n");
                }
            }
        }
        else
        {
            printf("\033[1;91m----------------------------------------\n");
            printf("| Keyword not found enter a valid one! |\n");
            printf("----------------------------------------\033[0m\n");
        }
    }
}
bool valid_email_or_not(char *temp_storage, AddressBook *addressBook)
{
    int i, size = strlen(temp_storage), count = 0;
    char *p = strchr(temp_storage, '@');    
    if(p == NULL)
    {
        return false;
    }
    for(i = 0; temp_storage[i] != '\0'; i++)       // validating email
    {
        if(temp_storage[i] == '@')
        {
            count++;
        }
        if(count > 1)
        {
            printf("\033[1;91m-----------------------------------------\n");
            printf("| E-MAIL should not contain multiple '@'! |\n");
            printf("-----------------------------------------\033[0m\n");
            return false;
        }
    }
    for(i = 0; i < p - temp_storage; i++)       // validating email
    {
        if(!isalnum(temp_storage[i]))
        {
            printf("\033[1;91m-----------------------------------------------------\n");
            printf("| E-MAIL should only contain alphabets and numbers! |\n");
            printf("-----------------------------------------------------\033[0m\n");

            return false;
        }
    }
    if(!isalpha(temp_storage[p - temp_storage + 1]) || temp_storage[size - 4] != '.')
    {
        printf("\033[1;91m-----------------------------------------------------\n");
        printf("| E-MAIL should only contain '.com' and alphabets after @ |\n");
        printf("-----------------------------------------------------\033[0m\n");
        return false;
    }
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(temp_storage, addressBook->contacts[i].email) == 0)
        {
            printf("\033[1;91m----------------------------------------\n");
            printf("| E-MAIL already exists enter new one! |\n");
            printf("----------------------------------------\033[0m\n");
            return false;
        }
    }
    return true;
}
bool valid_name_or_not(char *temp_storage, AddressBook *addressBook)  // validating name
{
    int i, size = strlen(temp_storage);
    if(size < 3)
    {
        printf("\033[1;91m-------------------------------------------------\n");
        printf("| Name should contain atleast three characters! |\n");
        printf("-------------------------------------------------\033[0m\n");
        return false;
    }
    if(isalpha(temp_storage[0]))
    {
        for(i = 1; i < size; i++)
        {
            if(temp_storage[i] == ' ' && isalpha(temp_storage[i + 1]))
            {
                i++;
            }
            else if(!isalpha(temp_storage[i]) || isupper(temp_storage[i]))
            {
                printf("\033[1;91m--------------------------------------------------------------------------\n");
                printf("| Name Should not contain numbers, extra space or any specail character! |\n");
                printf("--------------------------------------------------------------------------\033[0m\n");
                return false;
            }
        }
    }
    
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(temp_storage, addressBook->contacts[i].name) == 0)
        {
            printf("\033[1;91m--------------------------------------\n");
            printf("| Name already exists enter new one! |\n");
            printf("--------------------------------------\033[0m\n");
            return false;
        }
    }
    return true;
}
bool valid_phone_or_not(char *temp_storage, AddressBook *addressBook)
{
    int i, size = strlen(temp_storage);   // validating phone no
    if(size != 10)
    {
        printf("\033[1;91m---------------------------------------------------\n");
        printf("| phone number should contain exactly 10 numbers! |\n");
        printf("---------------------------------------------------\033[0m\n");
        return false;
    }
    if(temp_storage[0] < '6')
    {
        printf("\033[1;91m------------------------------------------\n");
        printf("| First number should start with(6 - 9)! |\n");
        printf("------------------------------------------\033[0m\n");
        return false;
    }
    for(i = 0; i < size; i++)
    {
        if(!isdigit(temp_storage[i]))
        {
            printf("\033[1;91m----------------------------------------------------\n");
            printf("| Phone number should contain only digits (0 - 9)! |\n");
            printf("----------------------------------------------------\033[0m\n");
            return false;
        }
    }
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(temp_storage, addressBook->contacts[i].phone) == 0)
        {
            printf("\033[1;91m----------------------------------------\n");
            printf("| Number already exists enter new one! |\n");
            printf("----------------------------------------\033[0m\n");
            return false;
        }
    }
    return true;
}   