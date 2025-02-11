#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <functional>
#include "Opcodes.cpp"
#include "Memory.cpp"

class CPU
{
private:
    static constexpr int NUM_OF_REG = 14;

    // Register indices
    static constexpr int INSTRUCTION_POINTER = 10; // r11
    static constexpr int CURRENT_PROCESS_ID = 11;  // r12
    static constexpr int STACK_POINTER_INDEX = 12; // r13
    static constexpr int GLOBAL_MEMORY_START = 13; // r14

    uint64_t clock = 0; // System clock
    std::vector<int64_t> registers;
    bool sign_flag = false;
    bool zero_flag = false;

    // Interrupt table (function pointers)
    std::unordered_map<std::string, std::function<void()>> interrupt_table;

    MemoryManager mem;

public:
    // Constructor
    CPU() : registers(NUM_OF_REG, 0)
    {
        registers[STACK_POINTER_INDEX] = 0xFFFFFFFF; // initialize stack pointer
    }

    ~CPU()
    {
        std::cout << "Deletes the CPU!" << std::endl; // for debugging
    }

    void executeInstruction(uint8_t op, uint32_t o1, uint32_t o2)
    {
        switch (op)
        {
        case 0x00: // increment instruction
            registers[o1]++;
            break;
        case 0x01: // addi
            registers[o1] += o2;
            break;
        case 0x02: // addr
            registers[o1] += registers[o2];
            break;
        case 0x03: // pushr
            break;
        case 0x04: // pushi
            break;
        case 0x05: // movi
            registers[o1] = o2;
            break;
        case 0x06: // movr
            registers[o1] = registers[o2];
            break;
        case 0x07:                                     // movmr
            uint8_t i = mem.readMemory(registers[o2]); // read the value from memory
            registers[o1] = i;                         // store it in register 1
            break;
        case 0x08: // movrm, write contenst of memory
            mem.writeToMemory(registers[o1], registers[o2]);
            break;
        case 0x09: // movmm
            mem.writeToMemory(o1, o2);
            // memory[registers[o1]] = memory[registers[o2]]
            break;
        case 0x0A: // printr
            std::cout << "Contents of register " << o1 << " are: " << registers[o1] << std::endl;
            break;
        case 0x0B: // printm
            std::cout << "Contents of memory at register " << o1 << " are: " << mem.readMemory(registers[o1]) << std::endl;
            break;
        case 0x0C: // printcr
            std::cout << "Contents of register " << o1 << " as a character are: " << static_cast<char>(registers[o1]) << std::endl;
            break;
        case 0x0D: // printcm
            std::cout << "Contents of mmemory at register " << o1 << " as a character are: " << static_cast<char>(mem.readMemory(registers[o1])) << std::endl;
            break;
        case 0x0E: // jmp
            registers[INSTRUCTION_POINTER] += registers[o1];
            break;
        case 0x0F: // jmpi
            registers[INSTRUCTION_POINTER] += o1;
            break;
        case 0x10: // jmpa
            registers[INSTRUCTION_POINTER] = o1;
            break;
        case 0x11: // cmpi. dont change register values
            // registers[o1] -= o2;
            if (registers[o1] < o2)
            {
                sign_flag = true;
                zero_flag = false;
            }
            else if (registers[o1] > o2)
            {
                sign_flag = false;
                zero_flag = false;
            }
            else if (registers[o1] == o2)
            {
                zero_flag = true;
                sign_flag = false;
            }
            break;
        case 0x12: // cmpr
            if (registers[o1] < registers[o2])
            {
                sign_flag = true;
                zero_flag = false;
            }
            else if (registers[o1] > registers[o2])
            {
                sign_flag = false;
                zero_flag = false;
            }
            else if (registers[o1] == registers[o2])
            {
                zero_flag = true;
                sign_flag = false;
            }
            break;
        case 0x13: // jlt
            if (sign_flag)
            {
                registers[INSTRUCTION_POINTER] += registers[o1];
            }
            break;
        case 0x14: // jlti
            if (sign_flag)
            {
                registers[INSTRUCTION_POINTER] += o1;
            }
            break;
        case 0x15: // jlta
            if (sign_flag)
            {
                registers[INSTRUCTION_POINTER] = o1;
            }
            break;
        case 0x16: // jgt
            if (!sign_flag)
            {
                registers[INSTRUCTION_POINTER] += registers[o1];
            }
            break;
        case 0x17: // jgti
            if (!sign_flag)
            {
                registers[INSTRUCTION_POINTER] += o1;
            }
            break;
        case 0x18: // jgta
            if (!sign_flag)
            {
                registers[INSTRUCTION_POINTER] = o1;
            }
            break;
        case 0x19: // je
            if (!zero_flag)
            {
                registers[INSTRUCTION_POINTER] += registers[o1];
            }
            break;
        case 0x1A: // jei
            if (!zero_flag)
            {
                registers[INSTRUCTION_POINTER] += o1;
            }
            break;
        case 0x1B: // jea
            if (!zero_flag)
            {
                registers[INSTRUCTION_POINTER] = o1;
            }
            break;
        case 0x1C: // call

            break;
        case 0x1D:
            break;
        case 0x1E:
            break;
        case 0x1F:
            break;
        case 0x20:
            break;
        case 0x21:
            break;
        case 0x22:
            break;
        case 0x23:
            break;
        case 0x24:
            break;
        case 0x25:
            break;
        case 0x26:
            break;
        default:
            std::cerr << "Unknown opcode: " << (int)op << std::endl;
            break;
        }
    }
};

#endif
