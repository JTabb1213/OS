#ifndef OPCODES_H
#define OPCODES_H
#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <cstdint>

enum Opcode : int
{
    INCR,
    ADDI,
    ADDR,
    PUSHR,
    PUSHI,
    MOVI,
    MOVR,
    MOVMR,
    MOVRM,
    MOVMM,
    PRINTR,
    PRINTM,
    PRINTCR,
    PRINTCM,
    JMP,
    JMPI,
    JMPA,
    CMPI,
    CMPR,
    JLT,
    JLTI,
    JLTA,
    JGT,
    JGTI,
    JGTA,
    JE,
    JEI,
    JEA,
    CALL,
    CALLM,
    RET,
    EXIT,
    POPR,
    POPM,
    SLEEP,
    INPUT,
    INPUTC,
    SETPRIORITY,
    SETPRIORITYI,
    DEST
};

#endif
