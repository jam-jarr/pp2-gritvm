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
void GritVM::CLEAR() {
    accumulator = long(0);
}
void GritVM::AT(int X) {
    accumulator = dataMem[X];
}
void GritVM::SET(int X) {
    dataMem[X] = accumulator;
}
void GritVM::INSERT(int X) {
    dataMem.insert(dataMem.begin() + X, accumulator);
}
void GritVM::ERASE(int X) {
    dataMem.erase(dataMem.begin() + X);
}
void GritVM::ADDCONST(long const c) {
    accumulator += c;
}
void GritVM::SUBCONST(long const c) {
    accumulator -= c;
}
void GritVM::MULCONST(long const c) {
    accumulator *= c;
}
void GritVM::DIVCONST(long const c) {
    accumulator /= c;
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
    if (jump < 0)
    {
        for (long i = 0; i < -jump; i++)
            currInstruct--;
    }
    else
    {
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
        instructMem.push_front(GVMHelper::parseInstruction(line));
    }
    inputFile.close();
    // call copy constructor
    dataMem = std::vector(initialMemory);
    return gritStatus;
}

std::vector<long> GritVM::getDataMem()
{
    // call copy constructor
    return std::vector(dataMem);
}

STATUS GritVM::reset()
{
    accumulator = 0;
    dataMem.clear();
    instructMem.clear();
    gritStatus = STATUS::WAITING;
}