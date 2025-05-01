#include "MemoryPager.h"

// Convert virtual address to physical address
int MemoryPager::translateAddress(int input)
{
    int page = (input >> 8) & 0xFFFFFF;             // Extract the 24-bit page
    int offset = input & 0xFF;                      // Extract the 8-bit offset
                                                    // std::cout << "Virtual Page: " << page
                                                    // << " with Offset: " << offset << std::endl;
    int pageLocationInMemory = pt.getTable()[page]; // look up the memory address of where the page starts in memory
    // std::cout << "Corresponding value for page " << page << " is: " << correspondingValue << std::endl;

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
    // int physicalPage = pageTable[page];
    int physicalAddress = pageLocationInMemory + offset;
    // std::cout << "mult " << page * 252 + offset << std::endl;
    // std::cout << "PHYSICAL ADDRESS IS: " << physicalAddress << std::endl;
    return physicalAddress;
}

// Read memory via virtual address
int MemoryPager::readMemory(int virtualAddress)
{
    // std::cout << "Virtual address recived was: " << virtualAddress << std::endl;
    int physicalAddress = translateAddress(virtualAddress);
    // std::cout << "Physical address is: " << physicalAddress << std::endl;
    if (physicalAddress == -1)
        return -1; // Invalid access
    // std::cout << "physical address is: " << physicalAddress << std::endl;
    // std::cout << "stuff at physical address is: " << memory.readMemory(physicalAddress) << std::endl;
    return memory.readMemory(physicalAddress);
}

// Write memory via virtual address
void MemoryPager::writeMemory(int virtualAddress, int value)
{
    int physicalAddress = translateAddress(virtualAddress);
    if (physicalAddress == -1)
        return; // Invalid access
    memory.writeToMemory(physicalAddress, value);
}

int MemoryPager::getMemSize()
{
    return memory.getMemorySize();
}

void MemoryPager::printPage(size_t pageNumber)
{
    size_t startIndex = pageNumber * 63; // 64 ints per page (256 bytes per page)
    size_t endIndex = startIndex + 63;   // 64 ints per page

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
