#include "../../bfscript.h"

#include <stdlib.h>
#include <sys/mman.h>

func_ptr BF_jit_compile(BF_state* state, const char* string) {
    char* memory = mmap(
        NULL, 4096,
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1, 0
    );

    

    return (func_ptr) memory;
}