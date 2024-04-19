#include "bfscript.h"

#include <stdio.h>

int main(int argvc, char** argv) {
    BF_state* state = BF_open_state(1024);

    BF_close_state(state);
    return 0;
}
