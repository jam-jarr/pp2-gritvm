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

    // instruction methods
    void ADDMEM(long X);
    void SUBMEM(long X);
    void MULMEM(long X);
    void DIVMEM(long X);
    void JUMPREL(long jump);
    void JUMPNZERO(long jump);
    void NOOP();
    void HALT();
    void OUTPUT();
    void CHECKMEM(long Z);
public:
    GritVM();
    ~GritVM();
    STATUS load(const std::string filename, const std::vector<long> &initialMemory) = 0;
};

#endif