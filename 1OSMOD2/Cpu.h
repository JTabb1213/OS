#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <functional>
#include "Opcodes.cpp"
#include "MemoryPager.h"
#include "PageTable.h"

class CPU
{
private:
    int NUM_OF_REG = 14;

    // Register indices
    int INSTRUCTION_POINTER = 10; // r11
    // int CURRENT_PROCESS_ID = 11;  // r12
    int STACK_POINTER_INDEX = 12; // r13
    // int GLOBAL_MEMORY_START = 13; // r14

    uint64_t clock = 0;
    std::vector<int> registers;
    bool sign_flag = false;
    bool zero_flag = false;
    int process_priority;

    // std::unordered_map<std::string, std::function<void()>> interrupt_table;

    MemoryPager &mem;
    PageTable &pageTable;

public:
    CPU(MemoryPager &memoryP, PageTable &pageTable) : registers(NUM_OF_REG, 0), mem(memoryP), pageTable(pageTable)
    {
        registers[STACK_POINTER_INDEX] = 63; // initialize stack pointer. since the highest memory location is 256 in a page, that will be our stack pointer
        // should point to the top location in memory, sice out instrcutions are 3 bytes, the stack pointer is size of memory - 3, or the
        // start of the last instruction in memory
        registers[INSTRUCTION_POINTER] = 0x00000000; // initialize the instruction pointer to be the first location in memory
    }

    ~CPU()
    {
        std::cout << "Deleted the CPU!" << std::endl; // for debugging
    }

    void fetchAndExectuteInstructions();

    void executeInstruction(int op, int o1, int o2);
};

#endif
