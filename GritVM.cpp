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
void GritVM::CLEAR()
{
    accumulator = long(0);
}
void GritVM::AT(int X)
{
    accumulator = dataMem[X];
}
void GritVM::SET(int X)
{
    dataMem[X] = accumulator;
}
void GritVM::INSERT(int X)
{
    dataMem.insert(dataMem.begin() + X, accumulator);
}
void GritVM::ERASE(int X)
{
    dataMem.erase(dataMem.begin() + X);
}
void GritVM::ADDCONST(long const c)
{
    accumulator += c;
}
void GritVM::SUBCONST(long const c)
{
    accumulator -= c;
}
void GritVM::MULCONST(long const c)
{
    accumulator *= c;
}
void GritVM::DIVCONST(long const c)
{
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
    std::cout << "Jumping by " << jump << " steps." << std::endl;
    if (jump == 0)
    {
        gritStatus = STATUS::ERRORED;
        return;
    }
    if (jump < 0)
    {
        // go back one more to account for while loop
        for (long i = 0; i < -jump + 1; i++)
        {
            currInstruct--;
            std::cout << "jumping..." << std::endl;
        }
    }
    else
    {
        // forward one less to account for while loop
        for (long i = 0; i < jump - 1; i++)
        {
            currInstruct++;
            std::cout << "jumping..." << std::endl;
        }
    }
}

void GritVM::JUMPZERO(long jump)
{
    if (accumulator == 0)
    {
        JUMPREL(jump);
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

void GritVM::OUTPUT()
{
    std::cout << accumulator << std::endl;
}

void GritVM::CHECKMEM(long X)
{
}

STATUS GritVM::load(const std::string filename, const std::vector<long> &initialMemory)
{
    std::fstream inputFile;
    inputFile.open(filename);
    std::string line;
    while (getline(inputFile, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }
        instructMem.push_back(GVMHelper::parseInstruction(line));
    }
    inputFile.close();
    // call copy constructor
    dataMem = std::vector<long>(initialMemory);
    return gritStatus;
}
STATUS GritVM::run()
{
    printVM(true, true);
    for (currInstruct = instructMem.begin(); currInstruct != instructMem.end(); currInstruct++)
    {
        printVM(true, false);
        std::cout << GVMHelper::instructionToString(currInstruct->operation) << " | " << currInstruct->argument << std::endl;
        if (gritStatus == STATUS::HALTED)
        {
            break;
        }
        evaluate(*currInstruct);
    }
    return gritStatus;
}
std::vector<long> GritVM::getDataMem()
{
    // call copy constructor
    return std::vector<long>(dataMem);
}

STATUS GritVM::reset()
{
    accumulator = 0;
    dataMem.clear();
    instructMem.clear();
    gritStatus = STATUS::WAITING;
    return gritStatus;
}

void GritVM::evaluate(Instruction i)
{
    switch (i.operation)
    {
    case INSTRUCTION_SET::CLEAR:
        CLEAR();
        break;
    case INSTRUCTION_SET::AT:
        AT(i.argument);
        break;
    case INSTRUCTION_SET::SET:
        SET(i.argument);
        break;
    case INSTRUCTION_SET::INSERT:
        INSERT(i.argument);
        break;
    case INSTRUCTION_SET::ERASE:
        ERASE(i.argument);
        break;
    case INSTRUCTION_SET::ADDCONST:
        ADDCONST(i.argument);
        break;
    case INSTRUCTION_SET::SUBCONST:
        SUBCONST(i.argument);
        break;
    case INSTRUCTION_SET::MULCONST:
        MULCONST(i.argument);
        break;
    case INSTRUCTION_SET::DIVCONST:
        DIVCONST(i.argument);
        break;
    case INSTRUCTION_SET::ADDMEM:
        ADDMEM(i.argument);
        break;
    case INSTRUCTION_SET::SUBMEM:
        SUBMEM(i.argument);
        break;
    case INSTRUCTION_SET::MULMEM:
        MULMEM(i.argument);
        break;
    case INSTRUCTION_SET::DIVMEM:
        DIVMEM(i.argument);
        break;
    case INSTRUCTION_SET::JUMPREL:
        JUMPREL(i.argument);
        break;
    case INSTRUCTION_SET::JUMPZERO:
        JUMPZERO(i.argument);
        break;
    case INSTRUCTION_SET::JUMPNZERO:
        JUMPNZERO(i.argument);
        break;
    case INSTRUCTION_SET::OUTPUT:
        OUTPUT();
        break;
    case INSTRUCTION_SET::CHECKMEM:
        CHECKMEM(i.argument);
        break;
    case INSTRUCTION_SET::NOOP:
        NOOP();
        break;
    case INSTRUCTION_SET::HALT:
        HALT();
        break;
    default:
        gritStatus = STATUS::ERRORED; // unknown instruction
        return;
    }
}

void GritVM::printVM(bool printData, bool printInstruction)
{
    using std::cout;
    using std::endl;
    cout << "****** Output Dump ******" << endl;
    cout << "Status: " << GVMHelper::statusToString(gritStatus) << endl;
    cout << "Accumulator: " << accumulator << endl;
    if (printData)
    {
        cout << "*** Data Memory ***" << endl;
        int index = 0;
        std::vector<long>::iterator it = dataMem.begin();
        while (it != dataMem.end())
        {
            long item = (*it);
            cout << "Location " << index++ << ": " << item << endl;
            it++;
        }
    }
    if (printInstruction)
    {
        cout << "*** Instruction Memory ***" << endl;
        int index = 0;
        std::list<Instruction>::iterator it = instructMem.begin();
        while (it != instructMem.end())
        {
            Instruction item = (*it);
            cout << "Instruction " << index++ << ": " << GVMHelper::instructionToString(item.operation) << " " << item.argument << endl;
            it++;
        }
    }
}

int main(int argc, char const *argv[])
{
    GritVM vm;
    long n1 = (rand() + 1) % 50;
    std::vector<long> initialMemory = { n1 };
    vm.load("test.gvm", initialMemory);
    vm.printVM(true, true);
    vm.run();
    vm.printVM(true, true);

    return 0;
}
