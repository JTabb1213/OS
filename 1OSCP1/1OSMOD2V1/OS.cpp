#include "OS.h"
#pragma GCC diagnostic ignored "-Wc++11-extensions"
void OS::setupInterruptTable()
{
    std::cout << "interupt table set!" << std::endl;
}

void OS::loadProgram()
{
    std::string filename = "a";
    memory.loadInstructionsIntoMemory(filename);
    std::cout << "Loaded into memory, before anything was exectuted: " << std::endl;
    memory.printMemory();
}

void OS::run()
{
    loadProgram(); // load the instruction set into memory
    // std::cout << "HERE" << std::endl;
    cpu.fetchAndExectuteInstructions();
    std::cout << "Contents of memory after instructions were executed: " << std::endl;
    memory.printMemory();
}