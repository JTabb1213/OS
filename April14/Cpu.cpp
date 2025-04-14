#include "Cpu.h"
#pragma GCC diagnostic ignored "-Wc++11-extensions"

static int currentPageIndex = 0;

void CPU::fetchAndExectuteInstructions()
{
    // pageTable.printOrder();
    // sort table on priority, with 1 being the highest
    std::sort(proTable.begin(), proTable.end(), [](const PCB &a, const PCB &b)
              { return a.priority < b.priority; });

    currentPageIndex = 0; // Track current page in the custom order

    for (const PCB &process : proTable) // for debugging
    {
        std::cout << process.state << std::endl;
    }
    std::cout << std::endl;

    // switch first process to running instead of queued
    // proTable[currentPageIndex].state = "running";
    while (true)
    {
        proTable[currentPageIndex].state = "running"; // switch current process to running instead of queued
        // std::cout << "HERE" << std::endl;
        int ip = registers[INSTRUCTION_POINTER]; // Get current instruction pointer (virtual address)
        // std::cout << "Instruction pointer is: " << ip << std::endl;
        int virtualPage = proTable[currentPageIndex].pageNumber; // Get the correct virtual page
        // std::cout << ip << std::endl;
        //  Convert virtual address to physical address using MMU

        // std::cout << "PHY " << physicalAddress << std::endl;

        // fetch instruction
        int opcode = mem.readMemory(ip);
        int op1 = mem.readMemory(ip + 1);
        int op2 = mem.readMemory(ip + 2);

        // execute instruction
        executeInstruction(opcode, op1, op2);

        // move to next instruction
        registers[INSTRUCTION_POINTER] += 3;

        // check if we reached the end of the current page (21 instructions = 63 ints)
        if ((registers[INSTRUCTION_POINTER] & 0xFF) == 63)
        {
            std::cout << "Reached the end of Page " << virtualPage << ", switching pages now!" << std::endl;
            proTable[currentPageIndex].state = "ended"; // before we switch however, make sure the process is marked as ended
            currentPageIndex++;                         // move to the next page in pageOrder
            if (currentPageIndex >= proTable.size())
            {
                std::cout << "Program execution complete!" << std::endl;
                return; // exit when all pages are executed
            }
            // std::cout << "HERE" << std::endl;
            int nextVirtualPage = proTable[currentPageIndex].pageNumber;
            registers[INSTRUCTION_POINTER] = (nextVirtualPage << 8) | 0x00;
            // std::cout << "Instruction pointer is now: " << registers[INSTRUCTION_POINTER] << std::endl;
            // std::cout << "HERE1" << std::endl;
        }
    }

    for (const PCB &process : proTable) // for debugging
    {
        std::cout << process.state << std::endl;
    }
    std::cout << std::endl;
}

/*
void CPU::fetchAndExectuteInstructions()
{
    // std::cout << "HERE" << std::endl;
    while (registers[INSTRUCTION_POINTER] < 63) // 63 ints, or 63/3 = 21 instructions per page.
    {
        // std::cout << "HERE" << std::endl;
        // std::cout << "IP is: " << registers[INSTRUCTION_POINTER] << std::endl;
        int ip = registers[INSTRUCTION_POINTER]; // get the value of the instruction we are supposed to execute

        int opcode = mem.readMemory(ip); // get the opcode and the two operand values for that opcode
        int op1 = mem.readMemory(ip + 1);
        int op2 = mem.readMemory(ip + 2);

        registers[INSTRUCTION_POINTER] += 3; // because in memory, every instrcution is stored every 12 bytes, or 3 int values, we need to increment our memory address by three to get the next instruction value.
        executeInstruction(opcode, op1, op2);
    }

    std::cout << "reached the end of the page, switching pages now!" << std::endl;
}
*/
void CPU::executeInstruction(int op, int o1, int o2)
{
    clock++; // increment the clock by 1 for each instruction
    switch (op)
    {
    case 0x00: // increment instruction
        // std::cout << "incremented" << std::endl;
        registers[o1]++;
        break;
    case 0x01: // addi
        // std::cout << "HERE" << o1 << " " << o2 << " " << std::endl;
        registers[o1] += o2;
        break;
    case 0x02: // addr
        registers[o1] += registers[o2];
        break;
    case 0x03:                                                          // pushr
        mem.writeMemory(registers[STACK_POINTER_INDEX], registers[o1]); // push the value stored at o1 to the address the stack is pointing to
        registers[STACK_POINTER_INDEX] -= 4;
        break;
    case 0x04: // pushi
        mem.writeMemory(registers[STACK_POINTER_INDEX], o1);
        registers[STACK_POINTER_INDEX] -= 4;
        break;
    case 0x05: // movi
        // std::cout << "HERE" << o1 << " " << o2 << std::endl;
        registers[o1] = o2;
        break;
    case 0x06: // movr
        registers[o1] = registers[o2];
        break;
    case 0x07:
    {                                          // movmr
        int i = mem.readMemory(registers[o2]); // read the value from memory
        registers[o1] = i;                     // store it in register 1
        break;
    }
    case 0x08: // movrm, write contenst of register o1 memory spot in registers[o2]
        // std::cout << "WR" << std::endl;
        mem.writeMemory(registers[o1], registers[o2]);
        break;
    case 0x09: // movmm
        mem.writeMemory(o1, o2);
        // memory[registers[o1]] = memory[registers[o2]]
        break;
    case 0x0A: // printr
        std::cout << "Contents of register " << o1 << " are: " << registers[o1] << std::endl;
        break;
    case 0x0B: // printm
        std::cout << "Contents of memory at register " << o1 << " are: " << mem.readMemory(registers[o1]) << std::endl;
        break;
    case 0x0C: // printcr
        std::cout << static_cast<char>(registers[o1]) << std::endl;
        break;
    case 0x0D: // printcm
        std::cout << "Contents of mmemory at register " << o1 << " as a character are: " << static_cast<char>(mem.readMemory(registers[o1])) << std::endl;
        break;
    case 0x0E: // jmp
        // std::cout << "HERE2" << std::endl;
        registers[INSTRUCTION_POINTER] += registers[o1];
        break;
    case 0x0F: // jmpi
        // std::cout << "HERE3" << std::endl;
        // std::cout << "Jumping: " << o1 << std::endl;
        registers[INSTRUCTION_POINTER] += o1;
        break;
    case 0x10: // jmpa
        registers[INSTRUCTION_POINTER] = o1;
        break;
    case 0x11: // cmpi. dont change register values
        // std::cout << "HERE1" << std::endl;
        //  registers[o1] -= o2;
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
        // std::cout << "HERE2" << std::endl;
        if (!zero_flag)
        {
            // std::cout << "HERE3" << std::endl;
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
        // std::cout << "Writing to memory value: " << registers[INSTRUCTION_POINTER] + 3 << " at location: " << registers[STACK_POINTER_INDEX] << std::endl;
        //  mem.writeToMemory(registers[STACK_POINTER_INDEX], registers[INSTRUCTION_POINTER] + 3);
        //   std::cout << "HERE4" << std::endl;
        //  registers[STACK_POINTER_INDEX] -= 4;

        // push the address of the next instruction to be executed first, before the instruction pointer is changed
        mem.writeMemory(registers[STACK_POINTER_INDEX], registers[INSTRUCTION_POINTER] + 3);
        registers[INSTRUCTION_POINTER] += registers[o1]; // call the subroutine at offset of what in register 2 from current instruction
        // registers[STACK_POINTER_INDEX] -= 4;
        //  std::cout << "Memory at location is: " << mem.readMemory(registers[STACK_POINTER_INDEX]) << std::endl;
        break;
    case 0x1D: // callm
        // std::cout << "Writing to memory value: " << registers[INSTRUCTION_POINTER] + 3 << std::endl;
        // registers[STACK_POINTER_INDEX] -= 4;

        // push the instruction onto the stack first
        mem.writeMemory(registers[STACK_POINTER_INDEX], registers[INSTRUCTION_POINTER] + 3);
        registers[INSTRUCTION_POINTER] += mem.readMemory(registers[o1]); // then change the current instruction to whatever is stored at memory location in register
        break;
    case 0x1E: // ret
               // set the instruction pointer address to the stack pointer address
        registers[INSTRUCTION_POINTER] = registers[STACK_POINTER_INDEX];
        break;
    case 0x1F: // exit, i chose to print the memory contents as well.
        std::cout << "Exiting." << std::endl;
        std::cout << "Memory contents of page 0 are: " << std::endl;
        mem.printPage(0);
        proTable[currentPageIndex].state = "ended"; // mark the current process as complete
        for (const PCB &process : proTable)         // for debugging
        {
            std::cout << process.state << std::endl;
        }
        std::cout << std::endl;
        exit(0);
        break;
    case 0x20: // popr
    {
        // get the contents at the top of the stack, or the contents in memory.
        int i = mem.readMemory(registers[STACK_POINTER_INDEX]);
        registers[o1] = i; // pop it into rx
        registers[STACK_POINTER_INDEX] -= 4;
        break;
    }
    case 0x21: // popm
    {
        // same thing as above but just write it to memory instead
        int i = mem.readMemory(registers[STACK_POINTER_INDEX]);
        mem.writeMemory(registers[STACK_POINTER_INDEX], i);
        break;
    }
    case 0x22: // sleep
        if (registers[o1] == 0)
        {
            std::cout << "Sleeping!" << std::endl;
        }
        else
        {
            int i = 0;
            std::cout << "Sleeping for " << registers[o1] << " cycles!" << std::endl;
            while (i < registers[o1])
            {
                i++;
                clock++; // also increment the clock
            }
        }
        break;
    case 0x23: // input
    {
        int number;
        std::cout << "Enter the number: ";
        std::cin >> number;
        registers[o1] = number;
        break;
    }
    case 0x24: // input c
    {
        char ch;
        std::cout << "Enter char: ";
        std::cin >> ch;
        registers[o1] = static_cast<int>(ch);
        break;
    }
    case 0x25: //
        process_priority = mem.readMemory(registers[o1]);
        break;
    case 0x26:
        process_priority = o1;
        break;
    default:
        std::cerr << "Error, unknown opcode: " << (int)op << std::endl;
        break;
    }
}