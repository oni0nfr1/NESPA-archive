#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define a 16807
#define m 2147483647
#define q 127773
#define r 2836

typedef struct {
    long seed;
} park_miller_t;

void park_miller_init(park_miller_t* rng, long seed) {
    if (seed <= 0) seed = 1;
    rng->seed = seed;
}

long park_miller_next(park_miller_t* rng) {
    long hi = rng->seed / q;
    long lo = rng->seed % q;
    long test = a * lo - r * hi;
    if (test > 0) {
        rng->seed = test;
    } else {
        rng->seed = test + m;
    }
    return rng->seed;
}

int park_miller_range(park_miller_t* rng, int min, int max) {
    return min + (park_miller_next(rng) % (max - min + 1));
}