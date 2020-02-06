#include <PCalc_T.h>
#include <pthread.h>
#include <math.h>
#include <thread>
#include <unistd.h>


/************************************************************************************************
 * PCalc_T (constructor) - Creates an array of primelist boolean objects with the size of
 *                       array_size and initializes them all to true. Also initializes number of
 *                       threads and the thread struct object.
 ************************************************************************************************/

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads) : PCalc(array_size), _num_threads(num_threads) {
    threads = new thread_data[_num_threads];
    _min_thread = 2;
    _max_thread = _num_threads;
}

/************************************************************************************************
 * PCalc_T (destructor) - deletes the primelist array
 ************************************************************************************************/

PCalc_T::~PCalc_T() {
    delete[] threads;
    cleanup();
}

/************************************************************************************************
 * markNonPrimes - sets all non primes numbers in primelist to false utililizing the number of 
                   alloted threads.
 ************************************************************************************************/

void PCalc_T::markNonPrimes() {
    PCalc::at(0) = false;
    PCalc::at(1) = false;

    unsigned int asize = PCalc::array_size();
    unsigned int srt = std::sqrt(asize);

    //spawn the requested number of threads
    for(unsigned int i = 0; i < _num_threads; i++) {
       threads[i].threadpos = i;
       threads[i].parray = this;
       threads[i].currentIndex = i+2;
       pthread_create(&threads[i].thread, NULL, PCalc_T::t_markprimes, &threads[i]);
    }

    //this block of codes keeps the min and max threads updated so that the worker threads know
    //what needs to be executed
    while(_min_thread < srt) {
        unsigned int min = asize;
        unsigned int max = 0;
        for(unsigned int i = 0; i < _num_threads; i++) {
            if(threads[i].currentIndex < min)
                min = threads[i].currentIndex;
            if(threads[i].currentIndex > max)
                max = threads[i].currentIndex;
        }
        _min_thread = min;
        _max_thread = max;
    }

    //wait for all the threads to finish
    for(unsigned int i = 0; i < _num_threads; i++) {
       pthread_join(threads[i].thread, NULL);
    }
}

/************************************************************************************************
 * t_markprimes - worker function for each thread that sets the non primes in prime list to false.
 ************************************************************************************************/

void *PCalc_T::t_markprimes(void *prt) {
    thread_data *thread = static_cast<thread_data *>(prt);
    unsigned int n = thread->parray->array_size();
    unsigned int srt = std::sqrt(n);

    //sleep until the threads that need to go before me has gone
    while(thread->parray->_min_thread < thread->currentIndex)
        usleep(1);

    //sieve algorithm
    while(thread->currentIndex < srt) {
        if(thread->parray->at(thread->currentIndex)) {
            for(unsigned int j = thread->currentIndex*thread->currentIndex; j < n; j += thread->currentIndex) {
                thread->parray->at(j) = false;
            }
        }
        //get the next index that needs to be run by this thread
        thread->currentIndex = thread->parray->_max_thread + 1;
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