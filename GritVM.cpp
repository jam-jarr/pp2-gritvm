#include <fstream>
#include <iostream>

#include "GritVM.hpp"
#include "GritVMBase.hpp" // Assuming STATUS is defined in GritVMBase.hpp

// implement instructions below
// dont forget to add their declaration to the header file

void GritVM::ADDMEM(long &a, long X) {
void GritVM::ADDMEM(long &a, long X)
{
    a += dataMem[X];
}

void GritVM::SUBMEM(long &a, long X)
{
    a -= dataMem[X];
}

void GritVM::MULMEM(long &a, long X)
{
    a *= dataMem[X];
}

void GritVM::DIVMEM(long &a, long X)
{
    a /= dataMem[X];
}

void GritVM::JUMPREL(long jump)
{
    currInstruct++;
}

void GritVM::JUMPNZERO(long jump)
{
    if (accumulator != 0)
    {
        currInstruct++;
    }
}

void GritVM::NOOP()
{
    // do nothing
}

void GritVM::HALT()
{
    gritStatus = STATUS::HALTED;
}
