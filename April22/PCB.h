#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <string>
#include <vector>

// Define the structure for a Process Control Block
struct PCB
{
    int pid;            // Process ID
    int code_size = 63; // 63 memory 'spots' for each page
    int data_size = 63; // 21 instructions, or 63 ints, or 252 bytes
    int stack_size = 63;
    int startOfHeap = 882;                                    // start of the second to last page, assuming a mem size of 1008.
    int endOfHeap = 944;                                      // end of heap
    int heapPage = 15;                                        // second to last page of the heap, which is 15 if the memsize is 1008
    int processsMemorySize = 1;                               // initialize it to one, could be more if more than 21 instructions
    std::string state;                                        // queued, running, sleeping, or ended
    std::vector<int> registerState = std::vector<int>(15, 0); // save the registers values when program ends
    bool sign_flag = false;
    bool zero_flag = false;
    int priority;           // Process priority
    int timeQuantum = 1000; // each process is initialiy allowed to run for 1000 clock cycles before being ended
    int clockCycles = 0;    // keep track of the clock cycles
    int sleepCounter = 0;   // if in waiting state, this is 0.
    int contextSwitches = 0;
    int pageNumber;
    int offset = 0;
    PCB() {}
};

#endif