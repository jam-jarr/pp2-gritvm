#include "GritVM.hpp"

// implement instructions below
// dont forget to add their declaration to the header file

void GritVM::ADDMEM(long &a, long X) {
    a += dataMem[X];
}