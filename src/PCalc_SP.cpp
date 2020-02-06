#include <PCalc_SP.h>
#include <iostream>
#include <math.h>

/************************************************************************************************
 * PCalc_SP (constructor) - Creates an array of primelist boolean objects with the size of
 *                       array_size and initializes them all to true. 
 ************************************************************************************************/

PCalc_SP::PCalc_SP(unsigned int array_size) : PCalc(array_size) {

}

/************************************************************************************************
 * PCalc_SP (destructor) - deletes the primelist array
 ************************************************************************************************/

PCalc_SP::~PCalc_SP() {
   cleanup();
}

/************************************************************************************************
 * markNonPrimes - sets all non primes numbers in primelist to false using sieve algorithm
 ************************************************************************************************/

void PCalc_SP::markNonPrimes() {
    PCalc::at(0) = false;
    PCalc::at(1) = false;

    unsigned int n = PCalc::array_size();
    unsigned srt = std::sqrt(n);

    for(unsigned int i = 2; i < srt; i++) {
        if(PCalc::at(i)) {
            for(unsigned int j = i*i; j < n; j += i) {
                PCalc::at(j) = false;
            }
        }
    }
}

/************************************************************************************************
 * printPrimes - outputs the prime values to the file specified
 *
 *    Params:  filename - the path/filename of the output file
 *
 ************************************************************************************************/

void PCalc_SP::printPrimes(const char *filename) {
    PCalc::printPrimes(filename);
}

/************************************************************************************************
 * cleanup - cleans up memory from this object
 ************************************************************************************************/

void PCalc_SP::cleanup() {
    PCalc::cleanup();
}