#pragma once

#include <math.h>
#include <random>

// Generates a Poisson-distributed random variable
inline static int GetPoisson(double lambda) {
  double L = exp(-lambda);
  double p = 1.0;
  int k = 0;

  do {
    k++;
    double random = ((double) rand() / (double) RAND_MAX);
    p *= random;
  } while (p > L);

  return k - 1;
}