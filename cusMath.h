#ifndef __CUSTOM_MATH__
#define __CUSTOM_MATH__
#include <vector>
#include <math.h>
double normalize2D(std::pair<double, double> v){
  double norm = 0;
  norm += v.first * v.first;
  norm += v.second * v.second;

  norm = std::sqrt(norm);
  return norm;
}
#endif