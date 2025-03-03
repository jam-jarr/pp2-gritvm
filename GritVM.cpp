// Name: Huy Bui U82390903
// Name: Jamie Giarratana U81686143
// Description: Source code for compiling the GritVM programming language
#include <fstream>
#include <iostream>

#include "GritVM.hpp"
#include "GritVMBase.hpp" // Assuming STATUS is defined in GritVMBase.hpp
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
/// Sets the accumulator to the value at X in the data memory
void GritVM::AT(int X)
{
    accumulator = dataMem[X];
}
/// Sets the value at X in the data memory to the value in the accumulator
void GritVM::SET(int X)
{
    dataMem[X] = accumulator;
}
/// Inserts in data memory at location X the value in the accumulator
void GritVM::INSERT(int X)
{
    dataMem.insert(dataMem.begin() + X, accumulator);
}
/// Erases location X in the DM
void GritVM::ERASE(int X)
{
    dataMem.erase(dataMem.begin() + X);
}
/// Adds C to the accumulator value
/// A = A + C
void GritVM::ADDCONST(long const c)
{
    accumulator += c;
}
/// Subtracts C from the accumulator
/// A = A – C
void GritVM::SUBCONST(long const c)
{
    accumulator -= c;
}
///Multiplies C to the accumulator value
///A = A * C
void GritVM::MULCONST(long const c)
{
    accumulator *= c;
}
///Divides C from the accumulator value
///A = A / C
void GritVM::DIVCONST(long const c)
{
    accumulator /= c;
}
///Adds DM[X] to the accumulator value
///A = A + DM[X]
void GritVM::ADDMEM(long X)
{
    accumulator += dataMem[X];
}
///Subtracts DM[X] from the accumulator
///A = A – DM[X]
void GritVM::SUBMEM(long X)
{
    accumulator -= dataMem[X];
}
///Multiplies DM[X] to the accumulator value
///A = A * DM[X]
void GritVM::MULMEM(long X)
{
    accumulator *= dataMem[X];
}
///Divides DM[X] from the accumulator value
///A = A / DM[X]
void GritVM::DIVMEM(long X)
{
    accumulator /= dataMem[X];
}
///Goes forward/back Y instructions from the current instruction (can be negative)
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
///Goes forward/back Y instructions from the current instruction (can be negative)
///if accumulator is 0. Otherwise just move forward 1 from the current instruction.
void GritVM::JUMPZERO(long jump)
{
    if (accumulator == 0)
    {
        JUMPREL(jump);
    }
}
///Goes forward/back Y instructions from the current instruction (can be negative)
/// if accumulator is not 0. Otherwise just move forward 1 from the current instruction.
void GritVM::JUMPNZERO(long jump)
{
    if (accumulator != 0)
    {
        JUMPREL(jump);
    }
}
///Perform no operation. Counts as an instruction but does nothing.
void GritVM::NOOP()
{
    // Jamie: do nothing
    // Huy: At first glance, the function seems to be "useless". However, its
    // existence suggest otherwise
}
///Stop the GritVM and switch status to HALTED
void GritVM::HALT()
{
    gritStatus = STATUS::HALTED;
}
///Output accumulator to std::cout
void GritVM::OUTPUT()
{
    std::cout << accumulator << std::endl;
}
///Checks to make sure DM is of at least size Z. If not, switch status to ERRORED
void GritVM::CHECKMEM(long X)
{
    if (dataMem.size() != int(X)){
        gritStatus = STATUS::ERRORED;
    }
}
/// Load instructions from .gvm file into instruction memory
STATUS GritVM::load(const std::string filename, const std::vector<long> &initialMemory)
{
    if (filename == ""){
        throw STATUS::ERRORED;
    }
    try {
        std::fstream inputFile;
        inputFile.open(filename);
        std::string line;
        while (getline(inputFile, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }
            instructMem.push_back(GVMHelper::parseInstruction(line));
        }
        inputFile.close();
    } catch(STATUS) {
        throw STATUS::ERRORED;
    }
    // call copy constructor
    dataMem = std::vector<long>(initialMemory);
    gritStatus = STATUS::READY;
    printVM(true, true);
    return gritStatus;
}
/// Run all instructions in instruction memory
STATUS GritVM::run()
{
    gritStatus = STATUS::RUNNING;
    for (currInstruct = instructMem.begin(); currInstruct != instructMem.end();
    currInstruct++)
    {
        printVM(true, true);
        std::cout << GVMHelper::instructionToString(currInstruct->operation) << " | " << currInstruct->argument << std::endl;
        evaluate(*currInstruct);
        if (gritStatus == STATUS::HALTED)
        {
            break;
        }
    }
    return gritStatus;
}
/// Return data in memory
std::vector<long> GritVM::getDataMem()
{
    // call copy constructor
    return std::vector<long>(dataMem);
}
/// Clear all parameters in GritVM
STATUS GritVM::reset()
{
    accumulator = 0;
    dataMem.clear();
    instructMem.clear();
    gritStatus = STATUS::WAITING;
    return gritStatus;
}
/// Helper function for run
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
/// Print debugging data to cout
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
