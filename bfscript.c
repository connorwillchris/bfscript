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

int BF_execute_string(BF_state* state, const char* string) {
    uint ptr = 0;

    while (*string) {
        switch(*string) {
            case '>':
                if (ptr >= state->len) {
                    ptr = 0;
                } else {
                    ptr++;
                }
                break;

            case '<':
                if (ptr == 0) {
                    ptr = state->len - 1;
                } else {
                    ptr--;
                }
                break;

            case '+':
                state->tape[ptr]++;
                break;
            
            case '-':
                state->tape[ptr]--;
                break;
            
            case '[':
                if (!state->tape[ptr]) {
                    int loop = 1;
                    while (loop > 0) {
                        string++;
                        if (*string == '[') loop++;
                        if (*string == ']') loop--;
                    }
                }
                break;
            
            case ']':
                if (state->tape[ptr]) {
                    int loop = 1;
                    while (loop > 0) {
                        string--;
                        if (*string == '[') loop--;
                        if (*string == ']') loop++;
                    }
                }
                break;
        }

        string++;
    }

    return 0;
}

int BF_execute_file(BF_state* state, const char* filepath) {

}

// no error checking
char BF_get_cell(BF_state* state, uint index) {
    return state->tape[index];
}

