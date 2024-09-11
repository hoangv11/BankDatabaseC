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
//  FILE:        template.h
//
//  DESCRIPTION:
//   Describe the file
//
****************************************************************/

#include "record.h"
#include <stdio.h>

extern int debug;
int addRecord(struct record **, int, char[], char[]);
void printAllRecords(struct record *);
int findRecord(struct record*, int);
int deleteRecord(struct record **, int);
int writefile(struct record *, char[]);
int readfile(struct record **, char[]);
void cleanup(struct record **); 
