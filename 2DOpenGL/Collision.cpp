#include "Collision.h"

bool Collision::boxBoxCollision(BoundingBox *a, BoundingBox* b)
{
	glm::vec3 aMin = a->getVMin();
	glm::vec3 aMax = a->getVMax();

	glm::vec3 bMin = b->getVMin();
	glm::vec3 bMax = b->getVMax();

	if (aMax.x > bMin.x &&
		aMin.x < bMax.x &&
		aMax.y > bMin.y &&
		aMin.y < bMax.y )
	{

		return true;
	}

	return false;
}

//find shortest distance between two intervals
/*
float Collision::compareIntervals(Interval i1, Interval i2)
{
	glm::vec3 vecChoice;
	if (i1.minVal < i2.minVal)
	{
		//interval 1 to the left
		vecChoice = i2.point1 - i1.point2;
	}
	else {
		//interval1 to the right
		vecChoice = i1.point1 - i2.point2;
	}

	float x2 = vecChoice.x*vecChoice.x;
	float y2 = vecChoice.y*vecChoice.y;
	float z2 = vecChoice.z*vecChoice.z;

	float sq = glm::sqrt(x2 + y2 + z2);


	return sq;

/ *
	//quick checks
	if (i2.minVal > i1.maxVal ||
		i1.minVal > i2.maxVal)
	{
		return 1.0f;
	}

	if ((i2.minVal < i1.maxVal &&
		i2.minVal > i1.minVal) ||
		(i1.minVal < i2.maxVal &&
		i1.minVal > i2.minVal))
	{
	

	}

* /

	


	
}*/



bool Collision::SATIntersection(BoundingBox *a, BoundingBox* b)
{
	

	for (int i = 0; i < a->getNumEdges(); i++)
	{

		glm::vec3 n = a->getEdge(i).normal;
		Interval ia = a->getInterval(n);
		Interval ib = b->getInterval(n);

		if (ia.maxVal < ib.minVal ||
			ib.maxVal < ia.minVal)
		{
			return false;
		}
	}



	for (int i = 0; i < b->getNumEdges(); i++)
	{

		glm::vec3 n = b->getEdge(i).normal;
		Interval ia = a->getInterval(n);
		Interval ib = b->getInterval(n);

		if (ia.maxVal < ib.minVal ||
			ib.maxVal < ia.minVal)
		{
			return false;
		}
	}

	return true;
}