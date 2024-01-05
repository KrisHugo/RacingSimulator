#ifndef __VECTOR2__
#define __VECTOR2__
#include <math.h>

#include "properties.h"

class Vector2
{
public:
	float x;
	float y;

	READONLY_PROPERTY(float, Length);
	GET(Length) 
	{ 
		return sqrt((x*x + y*y));
	}

	static Vector2 GetMaxLength(float maxLength, Vector2 direction){

	}
};

#endif