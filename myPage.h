#ifndef MYPAGE_H
#define MYPAGE_H

//create structure for page table 
struct Page {
    unsigned pFrames; // page frame number
    int bitPresent; //indicates whether this page is in physical memory
    int bitDirty; //indicates whether the page has been modified 

    Page(){
        this->pFrames = -1;
        this->bitPresent = -1;
        this->bitDirty = 0;
    }

    Page(unsigned pFrames){
        this->pFrames = pFrames;
        this->bitPresent = -1;
        this->bitDirty = 0;
    }

    Page(unsigned pFrames, int bitPresent){
        this->pFrames = pFrames;
        this->bitPresent = bitPresent;
        this->bitDirty = 0;
    }
};

//create void functions for page table
void myPageTable(struct pageTable pTable[], int sizeTable);

//creat void functions for cache 
void myCache(struct pageTable cacheMemory[], int sizeCache);
#endif