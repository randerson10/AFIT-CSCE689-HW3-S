#include <PCalc_T.h>
#include <pthread.h>
#include <math.h>
#include <thread>
#include <iostream>
#include <unistd.h>

struct thread_data {
    pthread_t thread;
    unsigned int threadpos;
    PCalc_T *parray;
    int start;
};

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads) : PCalc(array_size), _num_threads(num_threads) {

}

PCalc_T::~PCalc_T() {
   cleanup();
}

void PCalc_T::markNonPrimes() {
    int spawnedThreads = 0;
    thread_data threads[_num_threads];
    int n = PCalc::array_size();

    PCalc::at(0) = false;
    PCalc::at(1) = false;

    for(int i = 0; i < _num_threads; i++) {
       threads[i].threadpos = i;
       threads[i].parray = this;
    }


    
    for(int i = 2; i < sqrt(n); i++) {
        if(PCalc::at(i)) {
            if(spawnedThreads < _num_threads) {
                threads[spawnedThreads].start = i;
                _min_thread = i;
                pthread_create(&threads[spawnedThreads].thread, NULL, PCalc_T::t_markprimes, &threads[spawnedThreads]);
                spawnedThreads++;
            } else {
                for(int j = i*i; j < n; j += i) {
                    PCalc::at(j) = false;
                } 
            }
        }
    }

    for(int i = 0; i < _num_threads; i++) {
       pthread_join(threads[i].thread, NULL);
    }
}

void *PCalc_T::t_markprimes(void *prt) {
    thread_data *thread = static_cast<thread_data *>(prt);

    int i = thread->start;
    int n = thread->parray->array_size();

    // while(true) {
    //     std::cout << thread->parray->_min_thread << "\n";
    //     if(thread->parray->_min_thread > i)
    //         break;
    //     else
    //         usleep(1);
    // }
    for(int j = i*i; j < n; j += i) {
        thread->parray->at(j) = false;
    }
}


void PCalc_T::printPrimes(const char *filename) {
    PCalc::printPrimes(filename);
}

void PCalc_T::cleanup() {
    PCalc::cleanup();
}