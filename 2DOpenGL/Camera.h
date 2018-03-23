#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void setPosition(glm::vec3 p, bool add);
	glm::vec3 getPosition();

	glm::mat4 getCamMatrix() { return camMatrix; }

	void update(float dt);


	void updateCameraMatrix();



	///rotate across x axis
	void setYaw(float rot, bool add);
	///rotate across y axis
	void setPitch(float rot, bool add);
	///rotate across z axis
	void setRoll(float rot, bool add);


private:
	glm::vec3 pos;

	glm::mat4 baseMat;
	glm::mat4 camMatrix;



	//rotation
	///x axis rotation
	float rotPitch;
	///y axis rotation
	float rotYaw;
	///z-axis rotation
	float rotRoll;

	glm::vec3 camScale;
	


};