#include "PageTable.h"
// Print the page table (for debugging)
void PageTable::printTable()
{
    std::cout << "Page Table:\n";
    for (int page : order) // Iterate using order to maintain insertion sequence
    {
        std::cout << "Virtual Page " << page << " -> Physical Page " << table[page] << std::endl;
    }
}

void PageTable::printOrder()
{
    std::cout << "Order Vector: ";
    for (const auto &page : order)
    {
        std::cout << page << " ";
    }
    std::cout << std::endl;
}

std::vector<int> PageTable::getOrder()
{
    return order;
}

std::unordered_map<int, int> PageTable::getTable()
{
    return table;
}