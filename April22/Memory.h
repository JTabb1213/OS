
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Opcodes.cpp"
#include "PageTable.h"
#include "globals.h"

struct Instruction
{
    uint8_t opcode;
    uint32_t operand1;
    uint32_t operand2;
};

class MemoryManager
{
private:
    int MEMORY_SIZE; // size of memory, can change
    // int PAGE_SIZE = 64;
    std::vector<int> memory; // memory storage. Each value is 32 bits

    PageTable &pt;

public:
    MemoryManager(PageTable &pagetable, int memorySize) : pt(pagetable), MEMORY_SIZE(memorySize)
    {
        // MEMORY_SIZE = 1008;
        memory.resize(MEMORY_SIZE, 0);
    }

    int getMemorySize();
    int readMemory(int address);

    void writeToMemory(int address, int value);

    void writeMemory(int address, int opcode, int op1, int op2);

    void printMemory() const;

    int getHexOpcode(Opcode opcode);

    void loadInstructionsIntoMemory(std::string filename);
};

#endif
