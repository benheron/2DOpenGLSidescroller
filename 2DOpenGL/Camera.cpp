#include "Camera.h"

Camera::Camera() : pos(glm::vec3(0)), baseMat(glm::mat4(1)), camMatrix(glm::mat4(1)), rotPitch(0), rotYaw(0), rotRoll(0), camScale(glm::vec3(1))
{
	pos.z = 0;
	updateCameraMatrix();
}

Camera::~Camera()
{

}

void Camera::update(float dt)
{
	


}

void Camera::updateCameraMatrix()
{
	glm::mat4 mm = glm::mat4(1.0);


	mm = glm::translate(mm, pos);

	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	mm = glm::scale(mm, camScale);


	camMatrix = mm;
}

void Camera::setPosition(glm::vec3 p, bool add)
{
	if (add)
	{
		pos.x += p.x;
		pos.y += p.y;
	}
	else {
		pos.x = p.x;
		pos.y = p.y;
	}




	glm::mat4 mm = glm::mat4(1.0);

	camMatrix = glm::translate(baseMat, pos);
}

glm::vec3 Camera::getPosition()
{
	return pos;
}

void Camera::setYaw(float rot, bool add)
{
	if (add)
	{
		rotYaw += rot;
	}
	else {
		rotYaw = rot;
	}
	
}

void Camera::setPitch(float rot, bool add)
{
	if (add)
	{
		rotPitch += rot;
	}
	else {
		rotPitch = rot;
	}
	
}

void Camera::setRoll(float rot, bool add)
{
	if (add)
	{
		rotRoll += rot;
	}
	else {
		rotRoll = rot;
	}

}