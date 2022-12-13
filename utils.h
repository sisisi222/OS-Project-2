#ifndef READFILE
#define READFILE

//includes section
#include "myPage.h"
#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
//read a single entry from the trace file
void readAddress(FILE *f, unsigned &addr, char &rw);
unsigned int getPageNumber(unsigned addr);
int checkTable(std::vector<Page*> pageTable, unsigned addr);
void push(std::vector<Page*> *pageTable, Page* page);
void pop(std::vector<Page*> *pageTable);
void updateMemory(std::vector<Page*> *cacheMemory, Page* page);

#endif