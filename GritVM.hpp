#include "GritVMBase.hpp"
#include <vector>
#include <list>

#ifndef GRITVM
#define GRITVM

class GritVM : GritVMHelper
{
private:
    // private members
    std::vector<long> dataMem;
    std::list<Instruction> instructMem;
    std::list<Instruction>::iterator currInstruct;
    STATUS gritStatus;
   
    long accumulator;

    // instruction methods
    void CLEAR();
    void AT(int X);
    void SET(int X);
    void INSERT(int X);
    void ERASE(int X);
    void ADDCONST(long const c);
    void SUBCONST(long const c);
    void MULCONST(long const c);
    void DIVCONST(long const c);
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
    virtual STATUS load(const std::string filename, const std::vector<long> &initialMemory);
    virtual std::vector<long> GritVM::getDataMem();
    virtual STATUS GritVM::reset();
};

#endif