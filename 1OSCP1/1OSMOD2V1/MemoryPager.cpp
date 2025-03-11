#ifndef MEMORY_PAGER_H
#define MEMORY_PAGER_H

#include <vector>
#include <unordered_map>
#include "Memory.h"

class MemoryPager
{
private:
    MemoryManager &memory;
    int PAGE_SIZE = 256;
    std::unordered_map<int, int> pageTable; // page number to address in memory

public:
    MemoryPager(MemoryManager &memory) : memory(memory) {}

    // Convert virtual address to physical address
    int translateAddress(int input)
    {
        int page = (input >> 8) & 0xFFFFFF; // Extract the 24-bit page
        int offset = input & 0xFF;          // Extract the 8-bit offset

        // std::cout << page << "  " << offset << std::endl;

        // std::cout << "HERE!!!" << std::endl;
        /*
                if (pageTable.find(page) == pageTable.end())
                {
                    // std::cout << "HERE!!!" << std::endl;
                    std::cerr << "Page fault: Page " << page << " is not loaded!\n";
                    return -1;
                }
        */
        int physicalPage = pageTable[page];
        return (physicalPage * PAGE_SIZE) + offset;
    }

    // Read memory via virtual address
    int readMemory(int virtualAddress)
    {
        int physicalAddress = translateAddress(virtualAddress);
        if (physicalAddress == -1)
            return -1; // Invalid access
        return memory.readMemory(physicalAddress);
    }

    // Write memory via virtual address
    void writeMemory(int virtualAddress, int value)
    {
        int physicalAddress = translateAddress(virtualAddress);
        if (physicalAddress == -1)
            return; // Invalid access
        memory.writeToMemory(physicalAddress, value);
    }

    void printPage(size_t pageNumber)
    {
        size_t startIndex = pageNumber * 64; // 64 ints per page (256 bytes per page)
        size_t endIndex = startIndex + 64;   // 64 ints per page

        size_t counter = 0;
        for (size_t i = startIndex; i < endIndex; i++)
        {
            // Use the readMemory function from MemoryManager to access memory
            int value = memory.readMemory(i);

            // Check if the value is valid (optional)
            if (value != -1)
            {
                std::cout << std::hex << std::setw(8) << std::setfill('0') << value << " ";
            }

            if (counter == 2)
            {
                std::cout << std::endl;
                counter = 0;
            }
            else
            {
                counter++;
            }
        }
    }
};

#endif
