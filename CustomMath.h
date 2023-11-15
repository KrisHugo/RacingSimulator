#ifndef __CUSTOM_MATH__
#define __CUSTOM_MATH__
#include <vector>
#include <math.h>

#define vector2 std::pair<double, double>

static double normalize2D(vector2 v)
{
	double norm = 0;
	norm += v.first * v.first;
	norm += v.second * v.second;
	norm = std::sqrt(norm);
	return norm;
}
// static double cosV2D(vector2 v1, vector2 v2)
// {

// }
#endif