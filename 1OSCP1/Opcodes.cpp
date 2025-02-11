#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>

enum Opcode : uint8_t
{
    // Arithmetic Instructions
    INCR, // Increment register (r1 ⇐ r1 + 1)
    ADDI, // Add immediate value (r1 ⇐ r1 + #c)
    ADDR, // Add register (r1 ⇐ r1 + r2)

    // Stack Operations
    PUSHR, // Push register onto stack
    PUSHI, // Push immediate value onto stack
    POPR,  // Pop stack value into register
    POPM,  // Pop stack value into memory location

    // Move Instructions
    MOVI,  // Move immediate to register (r2 ⇐ #4)
    MOVR,  // Move register to register (r2 ⇐ r3)
    MOVMR, // Move memory to register (r2 ⇐ [r3])
    MOVRM, // Move register to memory ([r3] ⇐ r2)
    MOVMM, // Move memory to memory ([r2] ⇐ [r3])

    // Printing Instructions
    PRINTR,  // Print register contents
    PRINTM,  // Print memory contents
    PRINTCR, // Print register as a character
    PRINTCM, // Print memory contents as a character

    // Jump Instructions
    JMP,  // Jump relative (jmp r5 → IP += r5)
    JMPI, // Jump immediate (jmpi #36 → IP += 36)
    JMPA, // Jump absolute (jmpa #1234 → IP = 1234)

    // Comparison & Conditional Jumps
    CMPI, // Compare register to immediate (set flags)
    CMPR, // Compare register to register (set flags)
    JLT,  // Jump if less than (uses sign flag)
    JLTI, // Jump immediate if less than
    JLTA, // Jump absolute if less than
    JGT,  // Jump if greater than
    JGTI, // Jump immediate if greater than
    JGTA, // Jump absolute if greater than
    JE,   // Jump if equal (uses zero flag)
    JEI,  // Jump immediate if equal
    JEA,  // Jump absolute if equal

    // Function Calls
    CALL,  // Call function (relative)
    CALLM, // Call function (memory-based)
    RET,   // Return from function

    // Process & System Instructions
    EXIT,        // Terminate the program
    SLEEP,       // Sleep for X clock cycles
    INPUT,       // Read 64-bit value from keyboard
    INPUTC,      // Read a character from keyboard
    SETPRIORITY, // Set process priority
    SETPRIORITYI // Set process priority immediate
};

#endif
