#include "myPage.h"

void myPageTable(struct Page pTable[], int sizeTable) {
    int i;
    for(i = 0; i < sizeTable; i++) {
        pTable[i].pFrames = -1;
        pTable[i].bitPresent = -1;
        pTable[i].bitDirty = 0;
    }
}

void myCache(struct Page cacheMemory[], int sizeCache) {
    int i;
    for(i = 0; i < sizeCache; i++) {
        cacheMemory[i].pFrames = -1;
        cacheMemory[i].bitPresent = -1;
        cacheMemory[i].bitDirty = 0;
    }
}