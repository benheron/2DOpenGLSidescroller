#include "Camera.h"

Camera::Camera() : pos(glm::vec3(0)), baseMat(glm::mat4(1)), camMatrix(glm::mat4(1))
{

}

Camera::~Camera()
{

}

void Camera::update(float dt)
{

}

void Camera::setPosition(glm::vec3 p, bool add)
{
	if (add)
	{
		pos += p;
	}
	else {
		pos = p;
	}

	glm::mat4 mm = glm::mat4(1.0);

//	glm::vec3 intPos = glm::vec3((int)pos.x, (int)pos.y, (int)pos.z);


	camMatrix = glm::translate(baseMat, pos);
}

glm::vec3 Camera::getPosition()
{
	return pos;
}