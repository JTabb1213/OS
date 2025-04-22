#ifndef OS_H
#define OS_H

#include <iostream>
#include <vector>
#include <deque>
#include <cstdint>
#include <map>
#include <unordered_map>
#include <functional>
#include "Opcodes.cpp"
#include "Memory.h"
#include "Cpu.h"

class OS
{
private:
    CPU &cpu;
    MemoryManager &memory;
    std::deque<PCB> &processTable;
    // int next = 1;

public:
    OS(CPU &cpu, MemoryManager &memory, std::deque<PCB> &processTable) : cpu(cpu), memory(memory), processTable(processTable)
    {
        setupInterruptTable();
    }

    void setupInterruptTable();
    void loadProgram(const std::vector<std::string> &filenames);
    void run(const std::vector<std::string> &filenames);
};
#endif