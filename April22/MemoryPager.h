#ifndef MEMORY_PAGER_H
#define MEMORY_PAGER_H

#include <vector>
#include <unordered_map>
#include "Memory.h"
#include "PageTable.h"

class MemoryPager
{
private:
    MemoryManager &memory;
    PageTable &pt;
    // int PAGE_SIZE = 252;
    // int pageNumber = 0;
public:
    MemoryPager(MemoryManager &memory, PageTable &pt) : memory(memory), pt(pt) {}
    int getMemSize();

    // Convert virtual address to physical address
    int translateAddress(int input);

    // Read memory via virtual address
    int readMemory(int virtualAddress);

    // Write memory via virtual address
    void writeMemory(int virtualAddress, int value);

    void printPage(size_t pageNumber);
};

#endif
