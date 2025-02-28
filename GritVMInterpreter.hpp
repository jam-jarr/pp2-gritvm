#include "GritVMBase.hpp"
#include <vector>
#include <list>

#ifndef GRITVM
#define GRITVM

class GritVM : GritVMInterface
{
private:
    // private members
    std::vector<long> dataMem;
    std::list<Instruction> instructMem;
    std::list<Instruction>::iterator currInstruct;
    STATUS gritStatus;
    long accumulator;
public:
    // add instruction functions here
    void ADDMEM(long &a, long X);
};

#endif