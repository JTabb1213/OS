#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <deque>
#include <unordered_map>
#include <functional>
#include "Opcodes.cpp"
#include "MemoryPager.h"
#include "PageTable.h"
#include "PCB.h"

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
    MemoryManager &m;
    MemoryPager &mem;
    PageTable &pageTable;
    std::deque<PCB> &proTable;

public:
    CPU(MemoryManager &m, MemoryPager &memoryP, PageTable &pageTable, std::deque<PCB> &processTable) : registers(NUM_OF_REG, 0), m(m), mem(memoryP), pageTable(pageTable), proTable(processTable)
    {
        // initialize that stack pointer to the last virtual address (beggining of last page + offset of 63)
        int lastIntIndex = mem.getMemSize();
        int lastPage = lastIntIndex / 63;
        int offset = 63;

        int virtualAddress = (lastPage << 8) | offset;   // add 8 bits to the left and or those 0's with 63, effectivly getting it to the last spot in memory
        registers[STACK_POINTER_INDEX] = virtualAddress; // initialize stack pointer. since the highest memory location is 256 in a page, that will be our stack pointer
        // should point to the top location in memory, sice out instrcutions are 3 bytes, the stack pointer is size of memory - 3, or the
        // start of the last instruction in memory
        registers[INSTRUCTION_POINTER] = 0x00000000; // initialize the instruction pointer to be the first location in memory
        // registers[GLOBAL_MEMORY_START] = 0x333;
    }

    ~CPU()
    {
        std::cout << "Deleted the CPU!" << std::endl; // for debugging
    }

    void fetchAndExectuteInstructions();

    void executeInstruction(int op, int o1, int o2, std::deque<PCB> &d);
};

#endif
