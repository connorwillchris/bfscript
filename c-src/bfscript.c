#include <stdio.h>
#include <stdlib.h>

#include "bfscript.h"

/*
typedef struct BF_state {
    uint32_t tape_length;
    char* tape;
} BF_state;
*/

static int internal_syntax_error_checking(const char* string) {
    int there_are_brackets = 0;
    
    while (*string) {
        if (*string == '[') there_are_brackets++;
        if (*string == ']') there_are_brackets--;

        string++;
    }

    if (there_are_brackets) {
        fprintf(stderr, "[BF ERROR] | There was a syntax error. %d unclosed bracket(s) found.\n", there_are_brackets);
        return EnumRuntimeError_UnclosedBracket;
    }
    return EnumRuntimeError_None;
}

BF_state* BF_open_state(uint32_t tape_length) {
    BF_state* state = (BF_state*)malloc(sizeof(BF_state));
    state->tape_length = tape_length;
    state->tape = (char*)malloc(tape_length * sizeof(char));

    return state;
}

void BF_close_state(BF_state* state) {
    free(state);
}

int BF_execute_string(BF_state* state, const char* string) {
    int error = internal_syntax_error_checking(string);
    if (error) {
        return EnumRuntimeError_UnclosedBracket;
    }

    int tape_length = state->tape_length;
    uint32_t ptr = 0;
    
    while (*string) {
        switch(*string) {
            case '>':
                if (ptr >= tape_length) {
                    ptr = 0;
                } else {
                    ptr++;
                }
                break;

            case '<':
                if (ptr == 0) {
                    ptr = tape_length - 1;
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
            
            case '.':
                // TODO
                // execute a function here
                break;
        }

        string++;
    }

    return EnumRuntimeError_None;
}

int BF_execute_file(BF_state* state, const char* filepath) {
    FILE* file = fopen(filepath, "rb");
    if (file == NULL) {
        fprintf(stderr, "[BF ERROR] | File %s could not be opened.\n", filepath);
        return EnumRuntimeError_CouldNotOpenFile;
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "[BF ERROR] | Not enough memory to read file '%s'.\n", filepath);
        return EnumRuntimeError_NotEnoughMemory;
    }

    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (bytes_read < file_size) {
        fprintf(stderr, "[BF ERROR] | Could not read file '%s'.\n", filepath);
        return EnumRuntimeError_CouldNotReadFile;
    }
    buffer[bytes_read] = 0;

    int error = BF_execute_string(state, buffer);

    free(buffer);
    fclose(file);

    if (error) return error;
    return 0;
}

int BF_get_cell(BF_state* state, uint32_t index) {
    int tape_length = state->tape_length;
    if (index >= tape_length) {
        fprintf(stderr, "[BF ERROR] | Could not index value '%d'.\n", index);
        return EnumRuntimeError_CouldNotIndexCell;
    }
    return state->tape[index];
}
