#ifndef PCALC_T_H
#define PCALC_T_H

#include "PCalc.h"
#include <pthread.h>



// Your implementation of PCalc_T class should go here. 
// Make sure your constructor takes in two parameters:

// PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads);

// Call the parent constructor when initializing your constructor and pass in array_size. Then
// use num_threads to cap off how many threads you use to calculate all prime numbers
class PCalc_T : PCalc { 
    struct thread_data {
        pthread_t thread;
        unsigned int threadpos;
        PCalc_T *parray;
        int currentIndex;
    };

    public:
        PCalc_T(unsigned int array_size, unsigned int num_threads);
        ~PCalc_T();

        void markNonPrimes();
        void printPrimes(const char *filename);

        void cleanup();

    protected:
        static void *t_markprimes(void *prt);

    private:
        unsigned int _num_threads;
        int _min_thread = 2;
        int _max_thread = 0;
        thread_data threads[];
};


#endif
