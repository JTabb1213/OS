#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Memory.cpp" // Include the MemoryManager class
#include "Opcodes.cpp"
// #include "Cpu.cpp"
//  Function to load instructions from a file into memory

uint8_t getHexOpcode(Opcode opcode)
{
    return static_cast<uint8_t>(opcode);
}

// Function to load instructions from a file into memory
void loadInstructionsIntoMemory(MemoryManager &memoryManager, const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    uint32_t address = 0; // Starting address in memory

    while (std::getline(file, line))
    {
        // Process each line of the file, mapping string instruction to enum
        line.erase(std::remove(line.begin(), line.end(), ','), line.end()); // remove the commas
        std::cout << "Read line: " << line << std::endl;
        std::stringstream ss(line);
        std::string opcodeStr;
        ss >> opcodeStr;

        for (char &c : opcodeStr) // make the opcode all lowercase
        {
            c = tolower(c);
        }

        // Map the opcode string to the corresponding enum
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
        else if (opcodeStr == "popr")
        {
            opcode = Opcode::POPR;
        }
        else if (opcodeStr == "popm")
        {
            opcode = Opcode::POPM;
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
        // Function Calls
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
        // Process & System Instructions
        else if (opcodeStr == "exit")
        {
            opcode = Opcode::EXIT;
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
        else
        {
            std::cerr << "Unknown opcode: " << opcodeStr << std::endl;
            continue; // Skip this line if the opcode is unknown
        }

        std::string operand1, operand2, comma;
        // std::cout << "here1" << std::endl;
        ss >> operand1 >> operand2; // Extract two operands
        // std::cout << "Operand1: " << "\"" << operand1 << "\"  Operand two \"" << operand2 << std::endl;
        // handle empty operand values by setting to zero
        if (operand1.empty())
        {
            operand1 = "0";
        }

        if (operand2.empty())
        {
            operand2 = "0";
        }

        // handle constants
        if (operand1[0] == '$' && isdigit(operand1[1]))
        {
            operand1 = operand1.substr(1);
        }
        if (operand2[0] == '$' && isdigit(operand2[1]))
        {
            operand2 = operand2.substr(1);
        }

        // handle the @a operator by setting it to 97
        if (operand1 == "@a") // if its @a then its ascii value is a, or decimal 97
        {
            operand1 = "97";
        }
        if (operand2 == "@a") // if its @a then its ascii value is a, or decimal 97
        {
            operand2 = "97";
        }

        // Handle registers (rX → X)
        if (operand1[0] == 'r' && isdigit(operand1[1]))
        {
            operand1 = operand1.substr(1);
        }
        if (operand2[0] == 'r' && isdigit(operand2[1]))
        {
            operand2 = operand2.substr(1);
        }

        int op1 = std::stoi(operand1); // Convert operand1 to integer
        int op2 = std::stoi(operand2); // Convert operand2 to integer
        // std::cout << "here2" << std::endl;
        op1 = static_cast<uint32_t>(op1); // convert them to uint32_t values
        op2 = static_cast<uint32_t>(op2);
        //  Output the extracted information
        std::cout << "Opcode: " << opcodeStr << ", Operand1: " << operand1 << ", Operand2: " << operand2 << std::endl;

        uint8_t opcodeValue = getHexOpcode(opcode); // Get the corresponding hex value for the opcode
        std::cout << "Read opcode: " << opcodeStr << " (Hex: " << std::hex << (int)opcodeValue << std::dec << ")" << std::endl;

        // Write the opcode and arguments into memory (you can add more logic here for arguments)
        memoryManager.writeMemory(address, opcodeValue, op1, op2); // Write only the opcode value for now
        address += 9;                                              // Move to the next word in memory (you can add argument handling here)
    }

    file.close();
}

int main()
{
    // Create a MemoryManager object to handle memory operations
    MemoryManager memoryManager;

    // Load instructions from a file into memory
    std::string filename = "ins.txt"; // Replace with the actual filename containing instructions
    loadInstructionsIntoMemory(memoryManager, filename);

    // Print out the loaded instructions (for debugging purposes)
    std::cout << "Loaded instructions into memory:" << std::endl;
    memoryManager.printMemory();

    // now

    // Execute the instructions loaded into memory
    // std::cout << "Executing instructions:" << std::endl;
    // executeInstructions(memoryManager);

    return 0;
}

#pragma GCC diagnostic pop
