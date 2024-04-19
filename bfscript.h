#include <stdint.h>

typedef uint32_t uint;

typedef struct BF_state BF_state;

// Open a brainfuck state with a given tape length.
BF_state* BF_open_state(uint tape_len);

// Closes the brainfuck state when finished.
void BF_close_state(BF_state* state);

// Get a cell at a given index on the tape.
char BF_get_cell(BF_state* state, uint index);

// Get an array of cells from an index into a reference to value.
char* BF_get_cell_array(BF_state* state, uint index, char* value);

// Set a cell at a given index to a value.
void BF_set_cell(BF_state* state, uint index, char value);

// Set a cell array at a given index to a char array.
void BF_set_cell_array(BF_state* state, uint index, char* value);
