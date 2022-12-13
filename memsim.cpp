#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "fifo.hpp"
#include "lru.hpp"
#include "vms.hpp"

using namespace std;

int main(int argc, char** argv){

    //debug flag -> defaulted to quiet
    int debug = 0;
    
    //read trace file, passed in from argv[1]
    FILE *f = fopen(argv[1], "r");   
    if(!f){
        printf("No file found");
        return -1;
    }

    //convert argv[2] to integer representing number of mem frames
    int nframes = atoi(argv[2]);

    //check for method
    char* method = argv[3];
    if(!method){
        return -1;
    }
    
    //method handling
    //LRU
    if(strcmp(method, "lru") == 0 || strcmp(method, "LRU") == 0){

        //check for debug mode
        char* db = argv[4];
        if(strcmp(db, "debug") == 0){
            debug = 1;

        }

        if(debug) printf("Algorithm selected: lru\n");

        run_lru(f, nframes, debug);
    }
    //FIFO
    else if (strcmp(method, "fifo") == 0 || strcmp(method, "FIFO") == 0){

        //check for debug mode
        char* db = argv[4];
        if(strcmp(db, "debug") == 0){
            debug = 1;
        }

        if(debug) printf("Algorithm selected: fifo\n");

        run_fifo(f, nframes, debug);
    }
    //VMS
    else if(strcmp(method, "vms") == 0 || strcmp(method, "VMS") == 0){
        //get p from input and convert it to a float
        char* p = argv[4];
        float per = atof(argv[4]);

        //check for debug mode (NOTE that there is an extra parameter passed in for vms)
        char* db = argv[5];
        if(strcmp(db, "debug") == 0){
            debug = 1;
        }

        if(debug) printf("Algorithm selected: vms\n");

        run_vms(f, nframes, debug, per);
    }
    //NONE
    else{
        printf("Invalid algorithm: %s does not exist\n", method);
        return -1;
    }
}
