#include <iostream>
#include <string>
#include <cmath>
#include <time.h>


using namespace std;

// Constants ---------------------------------------------------------

const double pi = 3.1415926536;

// Output ------------------------------------------------------------

string lb = "\n\n"; // Line Break

// Timer -------------------------------------------------------------

clock_t clock_tic, clock_toc;

int tic() { clock_tic = clock(); return 0; } 

int toc() { 
    
    clock_toc = clock() - clock_tic;
    cout << "Time: " << (double)clock_toc/((double)CLOCKS_PER_SEC) 
        << "s." << lb; 

    return 0;

}

// Random ------------------------------------------------------------

// Generate Pseudorandom Double between 0.0 and max_i
double rand(double max_i) {

    const float scale = rand()/float(RAND_MAX);
    return scale*max_i;

}

// Keep it Peel.
