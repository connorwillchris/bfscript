#include "bfscript.h"

#include <stdio.h>

int main(int argvc, char** argv) {
    BF_state* state = BF_open_state(1024);

    // DEBUGGING AND TESTING
    BF_execute_string(state, ">++++++++[<++++++++>-]<+");

    char v = BF_get_cell(state, 0);
    printf("CHAR %c == ASCII %d\n", v, v);

    BF_close_state(state);
    return 0;
}
