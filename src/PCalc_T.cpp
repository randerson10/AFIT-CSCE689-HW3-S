#include <PCalc_T.h>
#include <pthread.h>
#include <math.h>
#include <thread>
#include <iostream>
#include <unistd.h>


/************************************************************************************************
 * PCalc_T (constructor) - Creates an array of primelist boolean objects with the size of
 *                       array_size and initializes them all to true. Also initializes number of
 *                       threads and the thread struct object.
 ************************************************************************************************/

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads) : PCalc(array_size), _num_threads(num_threads) {
    threads[_num_threads];
}

/************************************************************************************************
 * PCalc_T (destructor) - deletes the primelist array
 ************************************************************************************************/

PCalc_T::~PCalc_T() {
   cleanup();
}

/************************************************************************************************
 * markNonPrimes - sets all non primes numbers in primelist to false utililizing the number of 
                   alloted threads.
 ************************************************************************************************/

void PCalc_T::markNonPrimes() {
    PCalc::at(0) = false;
    PCalc::at(1) = false;

    for(int i = 0; i < _num_threads; i++) {
       threads[i].threadpos = i;
       threads[i].parray = this;
       threads[i].currentIndex = i+2;
       pthread_create(&threads[i].thread, NULL, PCalc_T::t_markprimes, &threads[i]);
    }

    while(_min_thread < PCalc::array_size()) {
        int min = _min_thread;
        int max = 0;
        for(int i = 0; i < _num_threads; i++) {
            if(threads[i].currentIndex < min)
                min = threads[i].currentIndex;
            if(threads[i].currentIndex > max)
                max = threads[i].currentIndex;
        }
        _min_thread = min;
        _max_thread = max;
       // std::cout << min << "\n";
    }


    for(int i = 0; i < _num_threads; i++) {
       pthread_join(threads[i].thread, NULL);
    }
}

/************************************************************************************************
 * t_markprimes - worker function for each thread that sets the non primes in prime list to false.
 ************************************************************************************************/

void *PCalc_T::t_markprimes(void *prt) {
    thread_data *thread = static_cast<thread_data *>(prt);
    int n = thread->parray->array_size();

    while(true) {
        //std::cout << "sleeping\n";
        if(thread->parray->_min_thread < thread->currentIndex)
            usleep(1);
        else
            break;
    }
    
    while(thread->currentIndex < sqrt(n)) {
        
        if(thread->parray->at(thread->currentIndex)) {
            for(int j = thread->currentIndex*thread->currentIndex; j < n; j += thread->currentIndex) {
                thread->parray->at(j) = false;
            }
        }

        thread->currentIndex = thread->parray->_max_thread + 1;


        

        
        // int max = 0;
        // for(int v = 0; v < thread->parray->_num_threads; v++) {
        //     if(thread->parray->threads[v].currentIndex > max)
        //         max = thread->parray->threads[v].currentIndex;

        // }
        // thread->currentIndex = max + 1;
    }
    
}

/************************************************************************************************
 * printPrimes - outputs the prime values to the file specified
 *
 *    Params:  filename - the path/filename of the output file
 *
 ************************************************************************************************/

void PCalc_T::printPrimes(const char *filename) {
    PCalc::printPrimes(filename);
}

/************************************************************************************************
 * cleanup - cleans up memory from this object
 ************************************************************************************************/

void PCalc_T::cleanup() {
    PCalc::cleanup();
}