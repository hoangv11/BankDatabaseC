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
//   Holds all the functions that can be used by the user and is accessed
//   through the user interface. 
//
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"


extern int debug;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   This function is used to add user information
//                 into a record.
//                 
//
//  Parameters:    struct record **start, int accountno, char name[]
//                 char  address[]
//                  
//  Return values:  0 : function success
//                 -1 : function failed
//
****************************************************************/

int addRecord(struct record **start, int accountno, char name[], char address[])
{
    struct record *nextRecord = NULL;
    struct record *current = NULL;
    struct record *temp = NULL;

    if(accountno < 0)
    {
        printf("Invalid account number");
        return -1;
    }

    temp = *start;
    while(temp != NULL)
    {
        if(temp->accountno == accountno)
        {
            printf("A record with that account number already exists\n");
            return -1;
        }
        temp = temp->next;
    }

    nextRecord = (struct record*) malloc(sizeof(struct record));

    
    nextRecord->accountno = accountno;
    strcpy(nextRecord->name, name);
    strcpy(nextRecord->address, address);
    nextRecord->next = NULL;

    if(*start == NULL || accountno < (*start)->accountno)
    {
        nextRecord->next = *start;
        *start = nextRecord;
        printf("Your record has been succesfully added.\n");
        return 0;
    }
    
    current = *start; 
        
    while(current->next != NULL)
    {
        temp = current->next;
        if(accountno == temp->accountno)
        {
            free(nextRecord);
            return -1;
        }
        if(accountno < temp->accountno)
        {
            nextRecord->next = temp;
            current->next = nextRecord;
            printf("Your record has been successfully added.\n");
            return 0;
        }
        current = current->next;
    }
    
    current->next = nextRecord;
    printf("Your record has been successfully added\n");
  
    if(debug == 1)
    {
        printf("DEBUG: adds record, called with int accountno, string name and address\n");
    }

    return 0; 
}

/*****************************************************************
//
//
//   Function name: printAllRecords
//
//   Description: This function prints all the information that is
//                currently stored in the record
//
//   Parameters:  struct record *start
//
//   Return values: void
//
//
******************************************************************/

void printAllRecords(struct record *start)
{

    struct record *current = start;
    
    if(current == NULL)
    {
        printf("There are no files on record.\n");
    }

    while(current != NULL)
    {
        printf("\nAccount Number: %d\n", current->accountno);
        printf("Name: %s", current->name);
        printf("Address: %s\n\n", current->address);
        
        current = current->next;
    }

    if(debug == 1)
    {
        printf("DEBUG: prints records, called with printAllRecords\n");
    }
}
 
/******************************************************************
//
//
//   Function name: findRecord
//
//   DESCRIPTION: This function finds and prints the record of a 
//                specified account number
//
//
//   Parameters:   struct record *start, int accountno
//
//   Return Values: 0: means the function successfully finds 
//                     and prints out the record
//
//                 -1: means that the function failed to find 
//                     the accountno on record
//
//
******************************************************************/ 

int findRecord(struct record *start, int accountno)
{
    struct record *current = start;

    while(current != NULL)
    {
        if(current->accountno == accountno) 
        {
            printf("\nAccount Number: %d\n", current->accountno);
            printf("Name: %s", current->name);
            printf("Address: %s\n", current->address);
            
            if(debug == 1)
            {
                printf("DEBUG: prints all records, called with int accountno");
            }
            return 0;
        }
        
        current = current->next;
    }

    printf("Couldn't find record with that account number\n");
    return -1;
}

/*******************************************************************
//
//
//    Function name: deleteRecord
//
//    DESCRIPTION: This function will delete a record with the 
//                  specific account number
//
//
//    Parameters:  struct record **start, int accountno
//
//
//    Return vales:  0: function successfully deletes account
//                  -1: function fails to find accountno
//
//
********************************************************************/

int deleteRecord(struct record **start, int accountno)
{
    struct record *current = *start;
    struct record *previous = NULL;
    int recordDeleted = -1;

    while(current != NULL && recordDeleted == -1)
    {
        if(current->accountno == accountno)
        {
            recordDeleted = 0;
            
            if(current == *start)
            {
                *start = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            
            free(current);
            printf("Record has been succesfully deleted\n");
            }
            else
            {
            previous = current;
            current = current->next;
            printf("Record not found\n");
            }
        }

    if(debug == 1)
    {
        printf("DEBUG: deletes a record, called with int accountno\n");
    }
    
    return recordDeleted; 
}

/**********************************************************************
//
//
//   Function name: Writefile
//
//   DESCRIPTION: writes data stored in record into a file that can be 
//                later accessed
//
//
//   Parameters:  struct record *start, char *filename
//
//   Return values: 0: success
//                 -1: fail
//
//
***********************************************************************/

int writefile(struct record *start, char filename[])
{
    FILE* filePointer;
    int result = 0;
    struct record *current = start;

    filePointer = fopen(filename, "w");
    if(filePointer == NULL)
    {
        result = -1;
    }
    
    while(current)
    {
        fprintf(filePointer, "Account Number: %d\n", current->accountno);
        fprintf(filePointer, "Name: %s", current->name);
        fprintf(filePointer, "Address: %s\n\n", current->address);
        
        current = current->next;
    }

    fclose(filePointer);

    if(debug == 1)
    {
        printf("DEBUG: saves all current records into a file on quit\n");
    }
    return result;
}

/***********************************************************************
//
//
//   Function name: readfile
//
//   DESCRIPTION: retrieves the records from a saved file
//
//   
//   Parameters:  struct record **start, char *filename
//
//   Return values: 0: success
//                 -1: failure
//
//
************************************************************************/

int readfile(struct record **start, char filename[])
{
    FILE* filePointer;
    int result = 0;
    int readSuccess = 1;
    struct record* current = NULL; 

    filePointer = fopen(filename, "r");
    if(filePointer == NULL)
    {
        result = -1;
    }
    else
    {
        while(readSuccess)
        {
            struct record* newRecord = (struct record*) malloc(sizeof(struct record));
       
            readSuccess = (fscanf(filePointer, "Account Number: %d\n", &newRecord->accountno) == 1);

            if(readSuccess)
            { 
                readSuccess = (fscanf(filePointer, "Name: %[^\n]\n", newRecord->name) == 1);
            }
            if(readSuccess)
            {
                readSuccess = (fscanf(filePointer, "Address: %[^\n]\n", newRecord->address) == 1);
            }
            if(readSuccess)
            {
                newRecord->next = NULL;
                if(*start == NULL)
                {
                    *start = newRecord;
                    current = *start;
                }
                else
                {   
                    current->next = newRecord;
                    current = current->next;
                }
            }
            else
            {
                free(newRecord);
            }
        }
        fclose(filePointer);
    }

    if(debug == 1)
    {
        printf("DEBUG: retrieves records from saved file\n");
    }
    
    return result;
} 

/******************************************************************************
//
//
//   Function name: cleanup
//
//
//   DESCRIPTION: This function deallocates memory, sets the start pointer to
//                NULL
//
//
//   Parameters: struct record **start
//
//   
//
//   Return values:  void
//
//
//
*******************************************************************************/  

void cleanup(struct record** start)
{
    struct record* current = *start;
    struct record* next = NULL;

    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    
    *start = NULL;

    if(debug == 1)
    {
        printf("DEBUG: All records are deallocated.\n");
    }
} 
