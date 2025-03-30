#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <unordered_map>
#include <iostream>
#include <vector>

class PageTable
{
private:
    std::unordered_map<int, int> table; // Map page number to memory location
    std::vector<int> order;             // unordered map wont track the order that they were added, so a separate vector is needed

public:
    PageTable()
    {
        table[2] = 63;
        table[1] = 126;
        table[0] = 0;

        order.push_back(0);
        order.push_back(1);
        order.push_back(2);

        // std::cout << "Constructor initialized page table:\n";
        // std::cout << "Virtual Page 0 -> " << table[0] << std::endl;
        // std::cout << "Virtual Page 1 -> " << table[1] << std::endl;
    }

    // Print the page table (for debugging)
    void printTable();
    void printOrder();

    std::unordered_map<int, int> getTable();
    std::vector<int> getOrder();
};

#endif
