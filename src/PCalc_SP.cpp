#include <PCalc_SP.h>
#include <iostream>
#include <math.h>

PCalc_SP::PCalc_SP(unsigned int array_size) : PCalc(array_size) {

}

PCalc_SP::~PCalc_SP() {
   cleanup();
}

void PCalc_SP::markNonPrimes() {
    PCalc::at(0) = false;
    PCalc::at(1) = false;

    int n = PCalc::array_size();
    //int sqrtN = (int)sqrt(double(n));
    for(int i = 2; i < sqrt(n); i++) {
        if(PCalc::at(i)) {
            for(int j = i*i; j < n; j += i) {
                PCalc::at(j) = false;
            }
        }
    }
}


void PCalc_SP::printPrimes(const char *filename) {
    PCalc::printPrimes(filename);
}

void PCalc_SP::cleanup() {
    PCalc::cleanup();
}