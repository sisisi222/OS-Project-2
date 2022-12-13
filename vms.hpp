#include "utils.h"

void run_vms(FILE *f, int nframes, int debug, float p){

    //address and read/write action
    unsigned int addr;
    char rw;

    //counters
    int readCount = 0, writeCount = 0, traceCount = 0, pageHits = 0, pageFaults = 0;

    //primary and secondary caches
    std::vector<Page*> primary;
    std::vector<Page*> secondary;

    //size limits for each cache based on nframes parameter
    int secondarySize = (int)((nframes * p) / 100);
    int primarySize = nframes - secondarySize;

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
            continue;
        }

        //extract page number fromn address
        unsigned pageNum = getPageNumber(addr);

        //check if the page is found in table
        int primaryCheck = checkTable(primary, pageNum);
        int secondaryCheck = checkTable(secondary, pageNum);
        if(debug && primaryCheck) std::cout << "Page hit for page number: " << pageNum << std::endl;
        if(debug && secondaryCheck) std::cout << "Page hit for page number: " << pageNum << std::endl;

        //PAGE HIT IN PRIMARY CACHE
        if(primaryCheck){
            //update R/W bit if write
            if(rwbit){
                for(auto *p : primary){
                    if(p->pFrames == pageNum){
                        p->bitDirty = 1;
                        break;
                    }
                }
            }
        }
        //PAGE HIT IN SECONDARY CACHE
        else if(secondaryCheck){
            for(auto *p : secondary){
                if(p->pFrames == pageNum){
                    Page *temp = p;

                    //update dirty bit
                    if(rwbit){
                        temp->bitDirty = 1;
                    }

                    //go through vector and remove the page
                    std::vector<Page*>::iterator iter = secondary.begin();
                    while(iter != secondary.end()){

                        //temporarily store page for comparison
                        Page t = **iter;
                        if(t.pFrames == temp->pFrames){
                            secondary.erase(iter);
                            break;
                        }
                        iter++;
                    }

                    //move temp to primary cache
                    push(&primary, temp);

                    //if primary is now full, move end to secondary
                    if(primary.size() > primarySize){
                        //pop/store last element in primary, add new page to primary
                        temp = primary[primary.size() - 1];
                        pop(&primary);

                        push(&secondary, temp);

                        if(secondary.size() >= secondarySize){
                            pop(&secondary);
                        }
                    }

                    break;
                }
            }
        }
        //PAGE FAULT
        else{

            Page *p = new Page(pageNum);

            //update r/w of the page
            if(rwbit){
                p->bitDirty = 1;
            }
            else{
                readCount++;
            }

            //check if we can add to fifo
            if(primary.size() < primarySize){
                push(&primary, p);
            }
            //check if we can add to lru
            else if(secondary.size() < secondarySize){
                Page* temp = primary[primary.size() - 1];
                pop(&primary);
                push(&primary, p);
                push(&secondary, temp);
            }
            //BOTH PRIMARY AND SECONDARY ARE FULL
            else{
                //pop/store last element in primary, add new page to primary
                Page* temp = primary[primary.size() - 1];
                pop(&primary);
                push(&primary, p);

                //pop final element from secondary
                if(secondary[secondary.size() - 1]->bitDirty == 1){
                    writeCount++;
                }
                pop(&secondary);
                push(&secondary, temp);
            }
        }
    }

    //print the algorithm results
    printf("Memory Frames: %d\n", nframes);
    printf("Events in trace: %d\n", traceCount);
    printf("Total disk reads: %d\n", readCount);
    printf("Total disk writes: %d\n", writeCount);

}