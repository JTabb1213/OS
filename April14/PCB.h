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
    // Add other relevant information as needed, such as:
    // - Memory management information
    // - I/O status information
    // - CPU registers
    PCB() {}
};

#endif