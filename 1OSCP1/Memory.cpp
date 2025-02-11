
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>

struct Instruction
{
    uint8_t opcode;
    uint32_t operand1;
    uint32_t operand2;
};

class MemoryManager
{
private:
    int MEMORY_SIZE;             // size of memory, can change
    std::vector<uint8_t> memory; // memory storage. Each value is 8 bits

public:
    // Constructor
    MemoryManager()
    {
        MEMORY_SIZE = 504;
        memory.resize(MEMORY_SIZE, 0);
    } // Initialize all memory to zero

    int getMemorySize() // returns the memory size for printing purposes
    {
        return MEMORY_SIZE;
    }
    // Read from memory (4-byte word)
    uint8_t readMemory(uint32_t address)
    {
        if (address >= MEMORY_SIZE)
        {
            throw std::out_of_range("Memory read out of bounds");
        }

        uint8_t i = memory[address];
        return i;
    }

    void writeToMemory(uint32_t address, uint8_t value)
    {
        if (address >= MEMORY_SIZE)
        {
            throw std::out_of_range("Memory read out of bounds");
        }

        memory[address] = value;
    }

    void writeMemory(uint32_t address, uint8_t opcode, uint32_t op1, uint32_t op2)
    {
        if (address + 9 > MEMORY_SIZE) // Ensure we're not out of bounds
        {
            throw std::out_of_range("Memory write out of bounds");
        }

        memory[address] = opcode; // Store the opcode (1 byte)

        // Store operand1 (4 bytes)
        memory[address + 1] = (op1 >> 24) & 0xFF;
        memory[address + 2] = (op1 >> 16) & 0xFF;
        memory[address + 3] = (op1 >> 8) & 0xFF;
        memory[address + 4] = (op1 >> 0) & 0xFF;

        // Store operand2 (4 bytes)
        memory[address + 5] = (op2 >> 24) & 0xFF;
        memory[address + 6] = (op2 >> 16) & 0xFF;
        memory[address + 7] = (op2 >> 8) & 0xFF;
        memory[address + 8] = (op2 >> 0) & 0xFF;
    }

    /*
        // Write to memory (4-byte word)
        void writeMemory(uint32_t address, uint8_t value, uint32_t op1, uint32_t op2)
        {
            if (address + 17 >= MEMORY_SIZE)
            {
                throw std::out_of_range("Memory write out of bounds");
            }
            memory[address] = value & 0xFF; // at address
            memory[address + 2] = op1 & 0xFFFFFFFF;
            memory[address + 10] = op2 & 0xFFFFFFFF;
            // memory[address + 3] = value & 0xFF;
        }
    */
    // Debugging: Print a memory range
    void printMemory() const
    {
        for (uint32_t i = 0; i < MEMORY_SIZE; i += 9) // Step by 9 bytes
        {
            // Print the 9 bytes of the instruction
            for (uint32_t j = 0; j < 9 && (i + j) < MEMORY_SIZE; ++j)
            {
                std::cout << std::hex << std::setw(2) << std::setfill('0')
                          << static_cast<int>(memory[i + j]) << " ";
            }

            std::cout << std::endl; // Newline after every 9 bytes
        }

        std::cout << std::dec << std::endl; // Reset to decimal output
    }
};

#endif
