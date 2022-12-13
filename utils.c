#include "utils.h"

//takes in a file and reads the next address
void readAddress(FILE *f, unsigned &addr, char &rw){
    fscanf(f, "%x %c", &addr, &rw);
}

//takes in address and bit shifts to extract the page number
unsigned int getPageNumber(unsigned addr){
    return (addr >> 12);
}

//given a page table vector and an address, check if the page exists in the page table
int checkTable(std::vector<Page*> pageTable, unsigned pageNum){
    for(int i = 0; i < pageTable.size(); i++){
        if(pageTable[i]->pFrames == pageNum){
            return 1;
        }
    }
    return 0;
}

//push a page to the front of the table
void push(std::vector<Page*> *pageTable, Page* page){
    pageTable->insert(pageTable->begin(), page);
}

//remove last element in vector
void pop(std::vector<Page*> *pageTable){
    pageTable->erase(--(pageTable->end()), pageTable->end());
}

//store all accessed pages to keep track of all bits
void updateMemory(std::vector<Page*> *cacheMemory, Page* page){
    /*
    for(auto p : cacheMemory){
        //page exists already
        //if(p.pFrames == page->pFrames){
        //    return;
        //}
    }
    //if not found, add it
    cacheMemory->push_back(page);  */
}