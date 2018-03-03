#pragma once

#include <math.h>
#include <cmath>
#include <algorithm> 
#include "BoundingBox.h"

struct FaceQuery {
	float largDist;
	int faceIndex;
};

struct EdgeQuery {

};

/**
@brief A collection of collision functions
*/
namespace Collision
{
	bool boxBoxCollision(BoundingBox *a, BoundingBox* b);

	float compareIntervals(Interval i1, Interval i2);

	bool SATIntersection(BoundingBox *a, BoundingBox* b);

	const float PI = 3.14159265359;

}


