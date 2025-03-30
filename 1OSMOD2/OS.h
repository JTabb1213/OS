#ifndef OS_H
#define OS_H

#include <iostream>
#include <vector>
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
    // int next = 1;

public:
    OS(CPU &cpu, MemoryManager &memory) : cpu(cpu), memory(memory)
    {
        setupInterruptTable();
    }

    void setupInterruptTable();
    void loadProgram();
    void run();
};
#endif