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
    long a; //accumulator
    // Private because these functions are used only according to the string
    // read from thr .gvm file
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
public:
    GritVM();


};

#endif