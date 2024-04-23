#include <stdio.h>

#include "bfscript.h"

int main(int argc, char** argv) {
    BF_state* state = BF_open_state(1024);

    func_ptr fn = BF_jit_compile(state, ">++++++++[<++++++++>-]<+");

    BF_close_state(state);
    return 0;
}
