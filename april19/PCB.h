#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <string>

// Define the structure for a Process Control Block
struct PCB
{
    int pid;            // Process ID
    std::string state;  // Process state (e.g., "running", "ready", "waiting", "terminated")
    int priority;       // Process priority
    int programCounter; // Program counter (address of the next instruction to be executed)
    int pageNumber;
    int sign_flag = false;
    int zero_flag = false;
    int code_size = 21;  // 21 instructions, or 63 ints, or 252 bytes
    int stack_size = 63; // one page of memory will be the stack, which is 63 ints

    // Add other relevant information as needed, such as:
    // - Memory management information
    // - I/O status information
    // - CPU registers
    PCB() {}
};

#endif