#pragma once


struct Edge {

	Edge(glm::vec3 start, glm::vec3 end) : start(start), end(end), dir(end - start), normal(glm::normalize(glm::vec3(-dir.y, dir.x, 0))) {
	}
	glm::vec3 start;
	glm::vec3 end;

	glm::vec3 dir;
	glm::vec3 normal;
};

struct Interval
{
	Interval(float minVal, float maxVal) : minVal(minVal), maxVal(maxVal) {}
	float minVal;
	float maxVal;
};

