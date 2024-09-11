/*****************************************************************
//
//  NAME:        Ravi Narayan
//
//  HOMEWORK:    1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        September 3, 2112
//
//  FILE:        template.c
//
//  DESCRIPTION:
//   Describe the file
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include "database.h"

void getaddress(char[], int);
void userMenu();

int debug = 0;

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Don't forget to describe what your main
//                 function does.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : some meaning
//                 -1 : some meaning
//
****************************************************************/

int main(int argc, char* argv[])
{
    struct record *start = NULL;
    int accountno;
    char name[30];
    char address[50];
    char userOption[20];
    int userMenuValid = 1;
    char filename[] = "records.txt";

    if(argc == 2 && strcmp(argv[1], "debug") == 0) 
    {
        debug = 1;
    }
    else if(argc > 1)
    {
        printf("debug: improper use\n");
        return 1;
    }

    readfile(&start, filename);
    
    printf("\nWelcome to the Bank\n"); 
    
    while(userMenuValid)
    {
        userMenu();
        scanf("%s", userOption);

        if(strlen(userOption) <= 3 && strncmp(userOption, "add", strlen(userOption)) == 0)
        {
            printf("Enter your account number: ");
            scanf("%d", &accountno);
            getchar();

            printf("Enter your name: ");
            fgets(name, 30, stdin);

            printf("Enter your address: ");
            getaddress(address, 50);

            addRecord(&start, accountno, name, address);
        }
        else if(strlen(userOption) <= 8 && strncmp(userOption, "printall", strlen(userOption)) == 0)
        {
            printAllRecords(start);
        }
        else if(strlen(userOption) <= 4 && strncmp(userOption, "find", strlen(userOption)) == 0)
        {
            printf("Enter account number you would like to find: ");
            scanf("%d", &accountno);
            findRecord(start, accountno); 
        }
        else if(strlen(userOption) <= 6 && strncmp(userOption, "delete", strlen(userOption)) == 0)
        {
            printf("Enter the account number you would like to delete: ");
            scanf("%d", &accountno);
            deleteRecord(&start, accountno); 
        }
        else if(strlen(userOption) <= 4 && strncmp(userOption, "quit", strlen(userOption)) == 0)
        {
            userMenuValid = 0;
            writefile(start, filename);
            cleanup(&start);
        }
        else
        {
            printf("Please enter a valid option\n");
        }    
    }

    return 0; 
}

/*****************************************************************
//
//  Function name: user_menu
//
//  DESCRIPTION:   This function displays the user menu which
//                 the user can see to use the commands to access 
//                 the database and its functions.           
//                 
//
//  Parameters:    ...
//
//  Return values:  0 : passes/success
//                 -1 : failed 
//
****************************************************************/

void userMenu()
{
    printf("\nSelect an option to continue...\n");
    printf("\nadd: add a new record into the system's database\n");
    printf("print: prints all records currently stored within the database\n");
    printf("find: find record of account number within the database\n");
    printf("delete: delete an existing record with account number\n");
    printf("quit: exit the program\n\n");
}

/******************************************************************
//
//
//   Function name: getaddress
//
//   DESCRIPTION: This function is used to obtain the address info
//                of the user who would like to add an account to 
//                the record
//
//   Parameters:
//
//   Return Values:
//
//
//
*******************************************************************/

void getaddress(char address[], int size) 
{
    int len = 0;
    int newLine = 0;
    int max = 0;
    char* result;

    while(!newLine && !max)
    {
        result = fgets(address + len, size, stdin);

        if(result)
        {
            newLine = (strlen(address + len) == 1);
            len = strlen(address);
            size = size - len;
            max = (size <= 1);
        }
        else
        {
            newLine = 1;
        }
    }
  
    if(len > 0 && address[len - 1] == '\n')
    {
        address[len - 1] = '\0';
    }
}
