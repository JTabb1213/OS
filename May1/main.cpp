#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include "Memory.h"
#include "Opcodes.cpp"
#include "Cpu.h"
#include "OS.h"
#include "MemoryPager.h"
#include "PageTable.h"
#include "PCB.h"
#include "globals.h"
#pragma GCC diagnostic ignored "-Wc++11-extensions"

int main(int argc, char *argv[])
{
    std::cout << "HERE: " << pageTrackerSwitchOn62 << std::endl;
    int memorySize = std::stoi(argv[1]); // memory size is the first arguement
    std::cout << "Command-line arguments:\n";
    for (int i = 0; i < argc; ++i)
    {
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }

    std::vector<std::string> filenames;
    int j = argc - 2;

    for (int i = 2; i < argc; ++i)
    {
        filenames.push_back(argv[i]);
    }

    std::deque<PCB> processTable;

    for (int i = 2; i < argc; ++i)
    {
        PCB process;

        process.pid = i; // or assign a unique PID if needed
        process.state = "loaded";
        process.priority = i - 1;   // priority starts at 1 for argv[2]
        process.pageNumber = i - 2; // page number starts at 0

        processTable.push_back(process);
    }

    std::sort(processTable.begin(), processTable.end(), [](const PCB &a, const PCB &b)
              { return a.priority < b.priority; });

    PageTable pt;
    // pt.printTable();
    //  pt.printOrder();
    MemoryManager memoryManager(pt, memorySize);
    // std::string filename = "ins1.txt";
    //  memoryManager.loadInstructionsIntoMemory(filename);
    // std::cout << "Loaded instructions into memory:" << std::endl;
    // memoryManager.printMemory();
    MemoryPager memorypager(memoryManager, pt);
    CPU cpu(memoryManager, memorypager, pt, processTable);
    OS os(cpu, memoryManager, processTable);
    os.run(filenames);
    // cpu.fetchAndExectuteInstrictions();
    return 0;
}

#pragma GCC diagnostic pop
