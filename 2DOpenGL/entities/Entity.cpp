#include "Entity.h"

Entity::Entity(glm::vec3 pos, glm::vec3 dimens) : pos(pos), dimensions(dimens)
{
	modelMatChanged = true;
	rotMatrix = glm::mat4(1.0);

	modelMatrix = glm::mat4(1.0);

	rotPitch = 0;
	rotYaw = 0;
	rotRoll = 0;

	modScale = glm::vec3(1.0);


	float size = 25.f;


	glm::vec2 topLeftVert = glm::vec2(pos.x, pos.y);
	glm::vec2 topRightVert = glm::vec2(pos.x + size, pos.y);
	glm::vec2 bottomLeftVert = glm::vec2(pos.x, pos.y + size);
	glm::vec2 bottomRightVert = glm::vec2(pos.x + size, pos.y + size);

	std::vector<glm::vec2> vertices;


	vertices.push_back(bottomLeftVert);
	vertices.push_back(topLeftVert);
	vertices.push_back(bottomRightVert);

	vertices.push_back(topRightVert);
	vertices.push_back(bottomRightVert);
	vertices.push_back(topLeftVert);



	std::vector<glm::vec2> UVs;

	glm::vec2 topLeftUV = glm::vec2(0.0f, 0.0f);
	glm::vec2 botLeftUV = glm::vec2(0.0f, 1.0f);
	glm::vec2 topRightUV = glm::vec2(1.0f, 0.0f);
	glm::vec2 botRightUV = glm::vec2(1.0f, 1.0f);


	UVs.push_back(topLeftUV);
	UVs.push_back(botLeftUV);
	UVs.push_back(topRightUV);

	UVs.push_back(botRightUV);
	UVs.push_back(topRightUV);
	UVs.push_back(botLeftUV);



	//above is upside down
	//below is for trying 0,0 as top left

	/*vertices.push_back(topLeftVert);
	vertices.push_back(bottomLeftVert);
	vertices.push_back(bottomRightVert);

	vertices.push_back(topRightVert);
	vertices.push_back(topLeftVert);
	vertices.push_back(bottomRightVert);*/

	model = new Model(vertices, UVs);


	forwardVec = glm::vec3(0, 0, 1);
	upVec = glm::vec3(0, 1, 0);
	rightVec = glm::vec3(-1, 0, 0);

	speed = 20;

	//bbAllowance = glm::vec3(0.1, 0.1, 0.8);
	bbAllowance = glm::vec3(0, 0, 0);

	moving = false;
	tilting = false;

}

Entity::~Entity()
{

}

void Entity::update(float dt)
{
	modelMatChanged = false;

	glm::mat4 mm = glm::mat4(1.0);


	//forwardVec = glm::rotate()

	//translate to new position
	mm = glm::translate(mm, pos);

	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	mm = glm::scale(mm, modScale);


	modelMatrix = mm;

	bb->transformByMat4(modelMatrix);
	

}


void Entity::setModel(Model *m)
{
	model = m;

	bb = new BoundingBox(model->getMinPos() + bbAllowance, model->getMaxPos() - bbAllowance);
}

glm::vec3 Entity::getPosition()
{
	return pos;
}

void Entity::setPosition(glm::vec3 p, bool add)
{
	if (add)
	{
		pos += p;
	}
	else {
		pos = p;
	}
	modelMatChanged = true;
}


void Entity::setYaw(float rot, bool add)
{
	if (add)
	{
		rotYaw += rot;
	}
	else {
		rotYaw = rot;
	}
	modelMatChanged = true;
}

void Entity::setPitch(float rot, bool add)
{
	if (add)
	{
		rotPitch += rot;
	}
	else {
		rotPitch = rot;
	}
	modelMatChanged = true;
}

void Entity::setRoll(float rot, bool add)
{
	if (add)
	{
		rotRoll += rot;
	}
	else {
		rotRoll = rot;
	}
	modelMatChanged = true;
}

Model* Entity::getModel()
{
	return model;
}

void Entity::setTexture(Texture *t)
{
	modTexture = t;
}

Texture *Entity::getTexture()
{
	return modTexture;
}


glm::mat4 Entity::getModelMatrix()
{
	if (!modelMatChanged)
	{
		return modelMatrix;
	}

	modelMatChanged = false;

	glm::mat4 mm = glm::mat4(1.0);


	//translate to new position
	mm = glm::translate(mm, pos);

	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	mm = glm::scale(mm, modScale);


	modelMatrix = mm;

	return modelMatrix;
}


void Entity::strafeLeft(float dt)
{
	
}

void Entity::strafeRight(float dt)
{
	
}

void Entity::moveForward(float dt)
{
	
}

void Entity::moveBackward(float dt)
{

}

void Entity::setScale(glm::vec3 s)
{
	modScale = s;
}

glm::vec3 Entity::getDimensions()
{


	return dimensions;


}

BoundingBox *Entity::getBoundingBox()
{
	return bb;
}

void Entity::moveRight(float dt)
{
	
}

void Entity::moveLeft(float dt)
{

}


float Entity::getRoll()
{
	return rotRoll;
}
