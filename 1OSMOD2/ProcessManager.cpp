#include <string>

struct PCB
{
    int pid;
    int pc;
    int registers[8];
    int page_table[10];
    std::string state;
    int priority;
};
