#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec3 vMin3, glm::vec3 vMax3)
{
	vMin = glm::vec4(vMin3, 1);
	vMax = glm::vec4(vMax3, 1);
}

BoundingBox::~BoundingBox()
{
	for (int i = 0; i < edges.size(); i++)
	{
		delete edges[i];
		delete newEdges[i];
	}
}

void BoundingBox::transformByMat4(glm::mat4 m)
{
	newVMin = m * vMin;
	newVMax = m * vMax;

}

glm::vec3 BoundingBox::getVMin()
{
	return glm::vec3(newVMin);
}

glm::vec3 BoundingBox::getVMax()
{
	return glm::vec3(newVMax);
}

void BoundingBox::generateVertsAndInds()
{
	
}


glm::vec3 BoundingBox::getSupport(glm::vec3 dir)
{
	float bestProjection = -99999;
	glm::vec3 bestVert = glm::vec3(-1);

	for (int i = 0; i < newVertices.size(); i++)
	{
		glm::vec3 v = newVertices[i];
		float projection = glm::dot(v, dir);

		if (projection > bestProjection)
		{
			bestProjection = projection;
			bestVert = v;
		}
	}

	return bestVert;
}

int BoundingBox::getNumEdges()
{
	return newEdges.size();
}

Edge* BoundingBox::getEdge(int index)
{
	return newEdges[index];
}

Interval BoundingBox::getInterval(glm::vec3 pAxis)
{
	float minVal, maxVal;

	minVal = maxVal = glm::dot(pAxis, newVertices[0]);

	for (int i = 1; i < newVertices.size(); i++)
	{
		float val = glm::dot(pAxis, newVertices[i]);

		minVal = std::min(minVal, val);	
		maxVal = std::max(maxVal, val);
	}

	Interval ival;
	ival.minVal = minVal;
	ival.maxVal = maxVal;

	return ival;
}