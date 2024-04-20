#include <stdio.h>

#include "bfscript.h"

int main(int argc, char** argv) {
    BF_state* state = BF_open_state(1024);

    // DEBUGGING AND TESTING
    interpret(state);
    
    char value = BF_get_cell(state, 0);
    printf("CHAR %c == ASCII %d\n", value, value);

    BF_close_state(state);
    return 0;
}
