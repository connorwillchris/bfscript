#include "./riscv_abi.h"
#include "./rv32i.h"

static const unsigned char INSTRUCTION_R_OPCODE = 0b0110011;

// R-Type instruction
static unsigned instruction_type_r(unsigned func3, unsigned func7, /*unsigned char opcode,*/ char rd, char rs1, char rs2) {
    unsigned value = 0;

    // apply the func7 portion.
    value = value << 7;
    value += func7;

    // apply the rs2 portion
    value = value << 5;
    value += rs2;

    // apply the rs1 portion
    value = value << 5;
    value += rs1;

    // apply the func3 portion
    value = value << 3;
    value += func3;

    // apply the rd portion
    value = value << 5;
    value += rd;

    // apply the opcode
    value = value << 7;
    value += INSTRUCTION_R_OPCODE;

    return value;
}

unsigned instruction_add(char rd, char rs1, char rs2) {
    // func3 = 0, and func7 = 0x0

    return instruction_type_r(0, 0, rd, rs1, rs2);
}

unsigned instruction_sub(char rd, char rs1, char rs2) {
    // func3 = 0, and func7 = 0x20

    return instruction_type_r(0, 0x20, rd, rs1, rs2);
}

unsigned instruction_xor(char rd, char rs1, char rs2) {
    // func3 = 0x4, and func7 = 0


    return instruction_type_r(0x4, 0, rd, rs1, rs2);
}

unsigned instruction_or(char rd, char rs1, char rs2) {
    // func3 = 0x6, and func7 = 0
    unsigned func3 = 0x6; unsigned func7 = 0;

    return instruction_type_r(func3, func7, rd, rs1, rs2);
}

unsigned instruction_and(char rd, char rs1, char rs2) {
    // func3 = 0x7, and func7 = 0
    unsigned func3 = 0x7; unsigned func7 = 0;

    return instruction_type_r(func3, func7, rd, rs1, rs2);
}

unsigned instruction_sll(char rd, char rs1, char rs2) {
    // func3 = 0x1, and func7 = 0
    unsigned func3 = 0x1; unsigned func7 = 0;

    return instruction_type_r(func3, func7, rd, rs1, rs2);
}

unsigned instruction_srl(char rd, char rs1, char rs2) {
    // func3 = 0x5, and func7 = 0
    unsigned func3 = 0x5; unsigned func7 = 0;

    return instruction_type_r(func3, func7, rd, rs1, rs2);
}

