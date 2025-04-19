#include "OS.h"
#pragma GCC diagnostic ignored "-Wc++11-extensions"
void OS::setupInterruptTable()
{
    std::cout << "interupt table set!" << std::endl;
}

void OS::loadProgram(const std::vector<std::string> &filenames)
{
    for (const auto &filename : filenames)
    {
        std::cout << "Loading file: " << filename << std::endl;
        memory.loadInstructionsIntoMemory(filename);
    }

    std::cout << "Loaded into memory, before anything was executed: " << std::endl;
    memory.printMemory();
}

void OS::run(const std::vector<std::string> &filenames)
{
    loadProgram(filenames); // load the instruction set into memory
    // std::cout << "HERE" << std::endl;
    cpu.fetchAndExectuteInstructions();
    for (const PCB &process : processTable) // for debugging
    {
        std::cout << process.state << std::endl;
    }
    // std::cout << "Contents of memory after instructions were executed: " << std::endl;
    memory.printMemory();
}