#include <iostream>
#include <string>
#include <cmath>

// Constants ---------------------------------------------------------

const double pi = 3.1415926536;

// Output ------------------------------------------------------------

string lb = "\n\n"; // Line Break

// Random ------------------------------------------------------------

// Generate Pseudorandom Double between 0.0 and max_i
double rand(double max_i) {

    const float scale = rand()/float(RAND_MAX);
    return scale*max_i;

}

// Keep it Peel.
