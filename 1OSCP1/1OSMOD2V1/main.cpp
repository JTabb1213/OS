#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Memory.h"
#include "Opcodes.cpp"
#include "Cpu.h"
#include "OS.h"
#include "MemoryPager.cpp"
#pragma GCC diagnostic ignored "-Wc++11-extensions"

int main()
{
    MemoryManager memoryManager;
    // std::string filename = "ins1.txt";
    //  memoryManager.loadInstructionsIntoMemory(filename);
    // std::cout << "Loaded instructions into memory:" << std::endl;
    // memoryManager.printMemory();
    MemoryPager memorypager(memoryManager);
    CPU cpu(memorypager);
    OS os(cpu, memoryManager);
    os.run();
    // cpu.fetchAndExectuteInstrictions();
    return 0;
}

#pragma GCC diagnostic pop
