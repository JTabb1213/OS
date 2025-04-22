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
        table[16] = 945; // last page, reserved for the stack. messed this up should be 15
        table[2] = 63;
        table[0] = 126;
        table[1] = 0;
        table[3] = 189;
        table[4] = 252;
        table[5] = 315;
        table[6] = 378;
        table[7] = 441;
        table[8] = 504;
        table[9] = 567;
        table[10] = 630;
        table[11] = 693;
        table[12] = 756;
        table[13] = 819;
        table[14] = 882;

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
