#include "utils.h"

void run_lru(FILE *f, int nframes, int debug){

    //address and read/write action
    unsigned int addr;
    char rw;

    //counters
    int readCount = 0, writeCount = 0, traceCount = 0, pageHits = 0, pageFaults = 0, hitCount = 0;

    //page table
    std::vector<Page*> pageTable;

    //read addresses until end of file 
    while(!feof(f)){
        //read address and increment traceCount;
        readAddress(f, addr, rw);
        traceCount++;
        int rwbit = 0;

        //increment R/W count based on rw char and update cache memory 
        if(rw == 'W' || rw == 'w'){
            rwbit = 1;
        }
        else if(rw == 'R' || rw == 'r'){
            rwbit = 0;
        }
        else{
            if(debug) std::cout << "R/W char not detected for character \"" << rw << "\"" << std::endl;
        }

        //extract page number fromn address
        unsigned pageNum = getPageNumber(addr);

        //check if the page is found in table
        int check = checkTable(pageTable, pageNum);
        if(debug && check) std::cout << "Page hit for page number: " << pageNum << std::endl;

        //PAGE HIT
        if(check){
            //update R/W bit if write
            for(auto *p : pageTable){
                    if(p->pFrames == pageNum){
                        Page *temp = p;

                        //update dirty bit
                        if(rwbit){
                            p->bitDirty = 1;
                        }

                        //go through vector and remove the page
                        std::vector<Page*>::iterator iter = pageTable.begin();
                        while(iter != pageTable.end()){
                            Page t = **iter;
                            if(t.pFrames == temp->pFrames){
                                pageTable.erase(iter);
                                break;
                            }
                            iter++;
                        }
                        //push page to the front
                        push(&pageTable, temp);
                        
                        break;
                    }
                }
        }
        //PAGE FAULT
        else {
            if(debug) std::cout << "Page fault for page number: " << pageNum << std::endl;
            Page *p = new Page(pageNum);

            //update r/w of the page
            if(rwbit){
                p->bitDirty = 1;
            }
            else{
                readCount++;
            }

            //table full, perform fifo swap
            if(pageTable.size() >= nframes){
                push(&pageTable, p);

                //if popping from back of the page table, check if that dirty bit is 1 and increment counter
                if(pageTable[pageTable.size() - 1]->bitDirty == 1){
                    writeCount++;
                }
                pop(&pageTable);
            }
            //table has room, just add the page
            else{
                push(&pageTable, p);
            }
        }
    }

    //print the algorithm results
    printf("Memory Frames: %d\n", nframes);
    printf("Events in trace: %d\n", traceCount);
    printf("Total disk reads: %d\n", readCount);
    printf("Total disk writes: %d\n", writeCount);
}