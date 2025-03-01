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
    long accumulator;
    GritVM();
    ~GritVM();

public:
    STATUS gritStatus;
    // add instruction functions here
    
    void ADDMEM(long &a, long X);
    void SUBMEM(long &a, long X);
    void MULMEM(long &a, long X);
    void DIVMEM(long &a, long X);
    void JUMPREL(long jump);
    void JUMPNZERO(long jump);
    void NOOP();
    void HALT();
    void OUTPUT();
    void CHECKMEM(long Z);
    STATUS load(const std::string filename, const std::vector<long> &initialMemory) = 0;
};

#endif