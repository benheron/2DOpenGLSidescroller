#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec3 vMin3, glm::vec3 vMax3, glm::vec3 offset) : offset(offset)
{
	vMin = glm::vec4(vMin3, 1);
	vMax = glm::vec4(vMax3, 1);

	newVMin = vMin;
	newVMax = vMax;

	generateVertsAndInds();
}

BoundingBox::~BoundingBox()
{
	
}

void BoundingBox::transformByMat4(const glm::mat4 &m)
{
	newVMin = (m * vMin);
	newVMax = (m * vMax);

	for (int i = 0; i < vertices.size(); i++)
	{
		glm::vec4 v = glm::vec4(vertices[i], 1);
		glm::vec4 newV = m * v;

		currentVerts[i] = glm::vec3(newV);
	}
	

	for (int i = 0; i < origEdges.size(); i++)
	{
		glm::vec4 n = glm::vec4(origEdges[i].normal, 0);

		glm::vec4 newN = m*n;
		currentEdges[i].normal = newN;
		
	}

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
	glm::vec3 topLeft = vMin;
	glm::vec3 topRight = glm::vec3(vMax.x, vMin.y, 0);
	glm::vec3 bottomLeft = glm::vec3(vMin.x, vMax.y, 0);;
	glm::vec3 bottomRight = vMax;

	Edge e1(topLeft, topRight);
	Edge e2(bottomLeft, topLeft);
	Edge e3(bottomRight, bottomLeft);
	Edge e4(topRight, bottomRight);

	origEdges.push_back(e1);
	origEdges.push_back(e2);
	origEdges.push_back(e3);
	origEdges.push_back(e4);

	currentEdges = origEdges;

	vertices.push_back(topLeft);
	vertices.push_back(topRight);
	vertices.push_back(bottomRight);
	vertices.push_back(bottomLeft);

	currentVerts = vertices;

	
}


/*
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
}*/

Interval BoundingBox::getInterval(glm::vec3 pAxis)
{
	float minVal, maxVal;

	minVal = maxVal = glm::dot(pAxis, currentVerts[0]);

	for (int i = 1; i < currentVerts.size(); i++)
	{
		float val = glm::dot(pAxis, currentVerts[i]);

		minVal = std::min(minVal, val);	
		maxVal = std::max(maxVal, val);
	}

	Interval ival(minVal, maxVal);

	return ival;
}