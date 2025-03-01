#include <fstream>
#include <iostream>

#include "GritVM.hpp"
#include "GritVMBase.hpp" // Assuming STATUS is defined in GritVMBase.hpp

// implement instructions below
// dont forget to add their declaration to the header file

GritVM::GritVM()
{
    // constructor
    gritStatus = STATUS::WAITING;
    accumulator = 0;
    currInstruct = instructMem.begin();
}

GritVM::~GritVM()
{
    dataMem.clear();
    instructMem.clear();
}

void GritVM::ADDMEM(long X)
{
    accumulator += dataMem[X];
}

void GritVM::SUBMEM(long X)
{
    accumulator -= dataMem[X];
}

void GritVM::MULMEM(long X)
{
    accumulator *= dataMem[X];
}

void GritVM::DIVMEM(long X)
{
    accumulator /= dataMem[X];
}

void GritVM::JUMPREL(long jump)
{
    if (jump < 0) {
        for (long i = 0; i < -jump; i++)
            currInstruct--;
    } else {
        for (long i = 0; i < jump; i++)
            currInstruct++;
    }
}

void GritVM::JUMPNZERO(long jump)
{
    if (accumulator != 0)
    {
        JUMPREL(jump);
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

STATUS GritVM::load(const std::string filename, const std::vector<long> &initialMemory)
{
    std::fstream inputFile;
    inputFile.open(filename);
    std::string line;
    while (getline(inputFile, line))
    {
        GVMHelper::parseInstruction(line);
    }
    inputFile.close();
    return gritStatus;
}