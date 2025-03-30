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
#include "MemoryPager.h"
#include "PageTable.h"
#pragma GCC diagnostic ignored "-Wc++11-extensions"

int main()
{
    PageTable pt;
    // pt.printTable();
    //  pt.printOrder();
    MemoryManager memoryManager(pt);
    // std::string filename = "ins1.txt";
    //  memoryManager.loadInstructionsIntoMemory(filename);
    // std::cout << "Loaded instructions into memory:" << std::endl;
    // memoryManager.printMemory();
    MemoryPager memorypager(memoryManager, pt);
    CPU cpu(memorypager, pt);
    OS os(cpu, memoryManager);
    os.run();
    // cpu.fetchAndExectuteInstrictions();
    return 0;
}

#pragma GCC diagnostic pop
