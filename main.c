#include <stdio.h>

#include "jit/riscv/rv32i.h"
#include "jit/riscv/riscv_abi.h"
#include "bfscript.h"

int main(int argc, char** argv) {
    BF_state* state = BF_open_state(1024);

    //func_ptr fn = BF_jit_compile(state, ">++++++++[<++++++++>-]<+");
    BF_execute_string(state, ">++++++++[<++++++++>-]<+");
    char v = BF_get_cell(state, 0);

    printf("A : %d\n", v);

    BF_close_state(state);

    //printf("add x5, x4, x3 = %08X\n", instruction_add(5, 4, 3));
    return 0;
}
