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


private:
	glm::vec3 pos;

	glm::mat4 baseMat;
	glm::mat4 camMatrix;
	


};