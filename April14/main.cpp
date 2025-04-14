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
#include "PCB.h"
#pragma GCC diagnostic ignored "-Wc++11-extensions"

int main(int argc, char *argv[])
{
    int memorySize = std::stoi(argv[1]); // memory size is the first arguement
    std::cout << "Command-line arguments:\n";
    for (int i = 0; i < argc; ++i)
    {
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }

    std::vector<std::string> filenames;
    for (int i = 2; i < argc; ++i)
    {
        filenames.push_back(argv[i]);
    }

    std::vector<PCB> processTable; // Store multiple processes (PCBs)

    PCB process1;

    // Initialize PCB members
    process1.pid = 1234;
    process1.state = "queued";
    process1.priority = 1;
    process1.programCounter = 0x1000;
    process1.pageNumber = 0; // page 0 starts at location 0 in memory

    processTable.push_back(process1);

    process1.pid = 1234;
    process1.state = "queued";
    process1.priority = 2;
    process1.programCounter = 0x1000;
    process1.pageNumber = 1; // page 1 is at the 126th byte

    processTable.push_back(process1);

    process1.pid = 1234;
    process1.state = "queued";
    process1.priority = 3;
    process1.programCounter = 0x1000;
    process1.pageNumber = 2; // page 2 is at the 63rd byte

    processTable.push_back(process1);

    PageTable pt;
    // pt.printTable();
    //  pt.printOrder();
    MemoryManager memoryManager(pt, memorySize);
    // std::string filename = "ins1.txt";
    //  memoryManager.loadInstructionsIntoMemory(filename);
    // std::cout << "Loaded instructions into memory:" << std::endl;
    // memoryManager.printMemory();
    MemoryPager memorypager(memoryManager, pt);
    CPU cpu(memorypager, pt, processTable);
    OS os(cpu, memoryManager);
    os.run(filenames);
    // cpu.fetchAndExectuteInstrictions();
    return 0;
}

#pragma GCC diagnostic pop
