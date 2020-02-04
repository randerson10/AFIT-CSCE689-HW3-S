#include <PCalc_T.h>
#include <pthread.h>
#include <math.h>
#include <thread>
#include <iostream>

struct thread_data {
    pthread_t thread;
    unsigned int threadpos;
    PCalc_T *parray;
};

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads) : PCalc(array_size), num_threads(num_threads) {

}

PCalc_T::~PCalc_T() {
   cleanup();
}

void PCalc_T::markNonPrimes() {
    PCalc::at(0) = false;
    PCalc::at(1) = false;

    thread_data threads[num_threads];

    for(int i = 0; i < num_threads; i++) {
       threads[i].threadpos = i;
       threads[i].parray = this;

       pthread_create(&threads[i].thread, NULL, PCalc_T::t_markprimes, &threads[i]);
    }

    for(int i = 0; i < num_threads; i++) {
       pthread_join(threads[i].thread, NULL);
    }
}

void *PCalc_T::t_markprimes(void *prt) {
    thread_data *thread = static_cast<thread_data *>(prt);

    int n = thread->parray->array_size();
    for(int i = thread->threadpos+2; i < sqrt(n); i++) {
        if(thread->parray->at(i)) {
            for(int j = i*i; j < n; j += i) {
                thread->parray->at(j) = false;
            }
        }
    }
}


void PCalc_T::printPrimes(const char *filename) {
    PCalc::printPrimes(filename);
}

void PCalc_T::cleanup() {
    PCalc::cleanup();
}