#include <stdio.h>
#include <stdlib.h>

#include "bfscript.h"

typedef struct BF_state {
    uint len;
    char* tape;
} BF_state;

BF_state* BF_open_state(uint tape_len) {
    BF_state* state = (BF_state*)malloc(sizeof(BF_state));
    state->len = tape_len;
    state->tape = (char*)malloc(tape_len * sizeof(char));
    
    return state;
}

void BF_close_state(BF_state* state) {
    free(state);
}

char BF_get_cell(BF_state* state, uint index) {
    // error checking
    if (index >= state->len) {
        fprintf(stdout, "[BF ERROR] | Index %d is not valid on the tape.\n", index);
        return 0;
    }

    return state->tape[index];
}

char* BF_get_cell_array(BF_state* state, uint index, char** array) {

}
