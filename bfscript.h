#include <stdint.h>

typedef unsigned int uint;

typedef struct BF_state BF_state;

typedef int (*BF_func)(BF_state*);

// Open a brainfuck state with a given tape length.
BF_state* BF_open_state(uint tape_len);

// Closes the brainfuck state when finished.
void BF_close_state(BF_state* state);

// Execute a given string.
int BF_execute_string(BF_state* state, const char* string);

// Execute a given file.
int BF_execute_file(BF_state* state, const char* filepath);

// Get a cell at a given index on the tape.
char BF_get_cell(BF_state* state, uint index);

// Get an array of cells from an index into a reference to value.
/* char* BF_get_cell_array(BF_state* state, uint index, char** value); */

// Set a cell at a given index to a value.
void BF_set_cell(BF_state* state, uint index, char value);

// Set a cell array at a given index to a char array.
void BF_set_cell_array(BF_state* state, uint index, char* value);

// Register a c function into the tape.
void BF_register_func(BF_func function, uint index);
