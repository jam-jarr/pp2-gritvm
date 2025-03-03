// Name: Huy Bui U82390903
// Name: Jamie Giarratana U81686143
// Description: Interface for GritVM programming language
#include <vector>
#include <list>
#include "GritVMBase.hpp"
#include "NodeList.hpp"
#ifndef GRITVM
#define GRITVM

class GritVM : GritVMInterface
{
private:
    // private members
    std::vector<long> dataMem;
    NodeList<_instruction> instructMem;
    NodeList<_instruction>::Iterator currInstruct;
    STATUS gritStatus;
    long accumulator;

    // instruction methods for GritVM
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
    void JUMPZERO(long jump);
    void JUMPNZERO(long jump);
    void NOOP();
    void HALT();
    void OUTPUT();
    void CHECKMEM(long Z);

    // helper methods
    void evaluate(Instruction i);
    
    public:
    GritVM();
    ~GritVM();
    virtual STATUS load(const std::string filename, const std::vector<long> &initialMemory);
    virtual std::vector<long> getDataMem();
    virtual STATUS reset();
    virtual STATUS run();

    // helper methods
    void printVM(bool printData, bool printInstruction);
};

#endif