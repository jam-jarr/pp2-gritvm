#include "GritVM.hpp"

// implement instructions below
// dont forget to add their declaration to the header file


void GritVM::CLEAR() {
    a = long(0);
}
void GritVM::AT(int X) {
    a = dataMem[X];
}
void GritVM::SET(int X) {
    dataMem[X] = a;
}
void GritVM::INSERT(int X) {
    dataMem.insert(dataMem.begin() + X,a);
}
void GritVM::ERASE(int X) {
    dataMem.erase(dataMem.begin() + X);
}
void GritVM::ADDCONST(long const c) {
    a += c;
}
void GritVM::SUBCONST(long const c) {
    a -= c;
}
void GritVM::MULCONST(long const c) {
    a *= c;
}
void GritVM::DIVCONST(long const c) {
    a /= c;
}

void GritVM::ADDMEM(long X) {
    a += dataMem[X];
}