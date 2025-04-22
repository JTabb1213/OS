#include "Memory.h"
#pragma GCC diagnostic ignored "-Wc++11-extensions"

int MemoryManager::getMemorySize() // returns the memory size for printing purposes
{
    return MEMORY_SIZE;
}

int MemoryManager::readMemory(int address)
{
    if (address >= MEMORY_SIZE)
    {
        throw std::out_of_range("Memory read out of bounds");
    }

    int i = memory[address];
    return i;
}

void MemoryManager::writeToMemory(int address, int value) // for loading file contents to memory
{
    if (address >= MEMORY_SIZE)
    {
        throw std::out_of_range("Memory read out of bounds");
    }

    memory[address] = value;
}

void MemoryManager::writeMemory(int address, int opcode, int op1, int op2)
{
    /*
// First, find the order of pages
std::vector<int> orderOfPages = pt.getOrder();
int currentPageIndex = 0;
int page = orderOfPages[currentPageIndex];
int writeToMemoryAt = pageNumberCurrentlyOn;
// int writeToMemoryAt = pt.getTable()[page]; // Get the memory address of the first page
// std::cout << "HEREHEREHERE: " << page << std::endl;
*/
    // pt.printTable();
    //  std::cout << "Writing to page: " << page << " At location: " << writeToMemoryAt << std::endl;
    int tracker = 0;
    std::unordered_map<int, int> tbl = pt.getTable();
    int pageLocationInMemory = tbl[pageNumberCurrentlyOn];
    // std::cout << "Page number is: " << pageNumberCurrentlyOn << " location is: " << pageLocationInMemory << std::endl;
    int location = pageLocationInMemory + pageTrackerSwitchOn62;
    // std::cout << "offset from location is: " << pageTrackerSwitchOn62 << std::endl;
    memory[location] = opcode;  // Store the opcode (1 byte)
    memory[location + 1] = op1; // Store the first operand (1 byte)
    memory[location + 2] = op2;
    // std::cout << "writing to memory at: " << location << std::endl;
}

void MemoryManager::printMemory() const // print memory 3 indexes each line
{
    size_t counter = 0;
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << memory[i] << " ";

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

int MemoryManager::getHexOpcode(Opcode opcode)
{
    return static_cast<int>(opcode);
}

void MemoryManager::loadInstructionsIntoMemory(std::string filename) // read file and write each line to memory
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    int address = 0;

    while (std::getline(file, line))
    {
        // std::cout << "HERE33333: " << pageTrackerSwitchOn62 << std::endl;
        line.erase(std::remove(line.begin(), line.end(), ','), line.end()); // remove the commas
        line.erase(std::remove(line.begin(), line.end(), '@'), line.end()); // remove the @
        line.erase(std::remove(line.begin(), line.end(), '$'), line.end()); // remove the constant value, or $ signs
        // line.erase(std::remove(line.begin(), line.end(), 'r'), line.end()); // remove the r's
        line = line.substr(0, line.find(";")); // delete the comments
        if (line.empty())
        { // if the line was a comment, continue
            continue;
        }
        // std::cout << "Read line: " << line << std::endl;
        std::stringstream ss(line);
        std::string opcodeStr;
        ss >> opcodeStr;

        for (char &c : opcodeStr) // make the opcode all lowercase
        {
            c = tolower(c);
        }

        // map the opcode string to the corresponding enum
        Opcode opcode;

        if (opcodeStr == "incr")
        {
            opcode = Opcode::INCR;
        }
        else if (opcodeStr == "addr")
        {
            opcode = Opcode::ADDR;
        }
        else if (opcodeStr == "addi")
        {
            opcode = Opcode::ADDI;
        }
        // Stack Operations
        else if (opcodeStr == "pushr")
        {
            opcode = Opcode::PUSHR;
        }
        else if (opcodeStr == "pushi")
        {
            opcode = Opcode::PUSHI;
        }
        // Move Instructions
        else if (opcodeStr == "movi")
        {
            opcode = Opcode::MOVI;
        }
        else if (opcodeStr == "movr")
        {
            opcode = Opcode::MOVR;
        }
        else if (opcodeStr == "movmr")
        {
            opcode = Opcode::MOVMR;
        }
        else if (opcodeStr == "movrm")
        {
            opcode = Opcode::MOVRM;
        }
        else if (opcodeStr == "movmm")
        {
            opcode = Opcode::MOVMM;
        }
        // Printing Instructions
        else if (opcodeStr == "printr")
        {
            opcode = Opcode::PRINTR;
        }
        else if (opcodeStr == "printm")
        {
            opcode = Opcode::PRINTM;
        }
        else if (opcodeStr == "printcr")
        {
            opcode = Opcode::PRINTCR;
        }
        else if (opcodeStr == "printcm")
        {
            opcode = Opcode::PRINTCM;
        }
        // Jump Instructions
        else if (opcodeStr == "jmp")
        {
            opcode = Opcode::JMP;
        }
        else if (opcodeStr == "jmpi")
        {
            opcode = Opcode::JMPI;
        }
        else if (opcodeStr == "jmpa")
        {
            opcode = Opcode::JMPA;
        }
        // Comparison & Conditional Jumps
        else if (opcodeStr == "cmpi")
        {
            opcode = Opcode::CMPI;
        }
        else if (opcodeStr == "cmpr")
        {
            opcode = Opcode::CMPR;
        }
        else if (opcodeStr == "jlt")
        {
            opcode = Opcode::JLT;
        }
        else if (opcodeStr == "jlti")
        {
            opcode = Opcode::JLTI;
        }
        else if (opcodeStr == "jlta")
        {
            opcode = Opcode::JLTA;
        }
        else if (opcodeStr == "jgt")
        {
            opcode = Opcode::JGT;
        }
        else if (opcodeStr == "jgti")
        {
            opcode = Opcode::JGTI;
        }
        else if (opcodeStr == "jgta")
        {
            opcode = Opcode::JGTA;
        }
        else if (opcodeStr == "je")
        {
            opcode = Opcode::JE;
        }
        else if (opcodeStr == "jei")
        {
            opcode = Opcode::JEI;
        }
        else if (opcodeStr == "jea")
        {
            opcode = Opcode::JEA;
        }
        else if (opcodeStr == "call")
        {
            opcode = Opcode::CALL;
        }
        else if (opcodeStr == "callm")
        {
            opcode = Opcode::CALLM;
        }
        else if (opcodeStr == "ret")
        {
            opcode = Opcode::RET;
        }
        else if (opcodeStr == "exit")
        {
            opcode = Opcode::EXIT;
        }
        else if (opcodeStr == "popr")
        {
            opcode = Opcode::POPR;
        }
        else if (opcodeStr == "sleep")
        {
            opcode = Opcode::SLEEP;
        }
        else if (opcodeStr == "input")
        {
            opcode = Opcode::INPUT;
        }
        else if (opcodeStr == "inputc")
        {
            opcode = Opcode::INPUTC;
        }
        else if (opcodeStr == "setpriority")
        {
            opcode = Opcode::SETPRIORITY;
        }
        else if (opcodeStr == "setpriorityi")
        {
            opcode = Opcode::SETPRIORITYI;
        }
        else if (opcodeStr == "dest")
        {
            opcode = Opcode::DEST;
        }
        else if (opcodeStr == "swi")
        {
            opcode = Opcode::SWI;
            // std::cout << "!!!!!!!!!!" << opcode << std::endl;
        }
        else
        {
            std::cerr << "Unknown opcode: " << opcodeStr << std::endl;
            continue;
        }

        std::string operand1, operand2;
        // std::cout << "here1" << std::endl;
        ss >> operand1 >> operand2; // Extract two operands
        // std::cout << "Operand1: " << "\"" << operand1 << "\"  Operand two \"" << operand2 << std::endl;
        //  handle empty operand values by setting to zero
        if (operand1.empty())
        {
            operand1 = "0";
        }

        if (operand2.empty())
        {
            operand2 = "0";
        }

        // handle registers by deleting the 'r'
        if (operand1[0] == 'r' && isdigit(operand1[1]))
        {
            operand1 = operand1.substr(1);
        }
        if (operand2[0] == 'r' && isdigit(operand2[1]))
        {
            operand2 = operand2.substr(1);
        }

        if (!operand2.empty() && isalpha(operand2[0]))
        {
            // std::cout << "HERE";
            operand2 = std::to_string(static_cast<int>(operand2[0]));
        }

        int op1 = std::stoi(operand1); // convert operand1 to integer
        int op2 = std::stoi(operand2); // convert operand2 to integer
        // std::cout << "here2" << std::endl;
        op1 = static_cast<int>(op1); // convert them to int values
        op2 = static_cast<int>(op2);
        //  output the extracted information
        // std::cout << "Opcode: " << opcodeStr << ", Operand1: " << operand1 << ", Operand2: " << operand2 << std::endl;

        int opcodeValue = getHexOpcode(opcode); // Get the corresponding hex value for the opcode
        // std::cout << "Read opcode: " << opcodeStr << " (Hex: " << std::hex << (int)opcodeValue << std::dec << ")" << std::endl;

        // write the opcode and arguments into memory
        writeMemory(address, opcodeValue, op1, op2);
        address += 3; // move to the next instruction spot in memory. Since each instruction takes up 24 bytes, and out vector is of ints, it would be 3 spots ahead.

        pageTrackerSwitchOn62 += 3;
        if (pageTrackerSwitchOn62 == 63)
        {
            pageTrackerSwitchOn62 = 0; // reset the
            pageNumberCurrentlyOn++;   // go to next page if file is over 63 instructions long
            // std::cout << pageTrackerSwitchOn63;
        }
    }
    pageNumberCurrentlyOn++;   // once eof is reached go to next page
    pageTrackerSwitchOn62 = 0; // also reset the counter
    // std::cout << "switched to page !!!!!!!!!!!!!!!!!!!!!!!!" << pageNumberCurrentlyOn << std::endl;
    //  std::cout << "HERE" << std::endl;

    file.close();
}