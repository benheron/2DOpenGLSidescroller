#include "Entity.h"


Entity::Entity(Texture* entTexture, glm::vec3 pos, glm::vec3 dimens2, glm::vec2 uvSize2) : entTexture(entTexture), pos(pos), dimens(dimens2), uvSize(uvSize2)
{
	entTextures.push_back(entTexture);

	if (dimens == glm::vec3(0))
	{
		dimens = glm::vec3(entTexture->getOrigDimens(), 0);
	}

	if (uvSize == glm::vec2(0))
	{
		uvSize = glm::vec2(1);
	}

	container = false;

	offsetPos = glm::vec3(dimens.x / 2, dimens.y / 2, 0);

	init();
}


Entity::Entity(glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : pos(pos),  dimens(dimens), uvSize(uvSize), offsetPos(offPos), container(container)
{
	
	if (offPos == glm::vec3(0))
	{
		offsetPos = glm::vec3(dimens.x / 2, dimens.y / 2, 0);

	}
	
	init();
}

Entity::~Entity()
{

}


void Entity::init()
{
	modelMatChanged = true;
	rotMatrix = glm::mat4(1.0);

	modelMatrix = glm::mat4(1.0);

	rotPitch = 0;
	rotYaw = 0;
	rotRoll = 0;

	modScale = glm::vec3(1.0);


	speed = 150;


	setQuadVertices(vertices);



	if (entTexture != NULL && uvSize != glm::vec2(0))
	{
		
		setQuadUVs(UVs);

		model = new Model(vertices, UVs);

		entModels.push_back(model);
	}
	else {
		if (!container)
		{
			model = new Model(vertices);
		}
		
	}
	

	updateModelMatrix();

}

void Entity::update(float dt)
{

	if (!modelMatChanged)
	{
		return;
	}

	updateModelMatrix();

	//bb->transformByMat4(modelMatrix);
	

}


void Entity::updateModelMatrix()
{
	modelMatChanged = false;

	glm::mat4 mm = glm::mat4(1.0);

	glm::vec3 jointPos = pos + offsetPos;// +glm::vec3(0.5, 0.5, 0);

	//glm::vec3 nPos = glm::vec3((int)jointPos.x, (int)jointPos.y, (int)jointPos.z);

	glm::vec3 nPos = glm::vec3(jointPos.x, jointPos.y, jointPos.z);

	

	//translate to new position
	mm = glm::translate(mm, nPos);

	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	mm = glm::scale(mm, modScale);


	modelMatrix = mm;
}




void Entity::setQuadVertices(std::vector<glm::vec2> &vertices)
{
	

	glm::vec3 startPos = pos - offsetPos;


	glm::vec2 topLeftVert = glm::vec2(startPos.x, startPos.y);
	glm::vec2 topRightVert = glm::vec2(startPos.x + dimens.x, startPos.y);
	glm::vec2 bottomLeftVert = glm::vec2(startPos.x, startPos.y + dimens.y);
	glm::vec2 bottomRightVert = glm::vec2(startPos.x + dimens.x, startPos.y + dimens.y);



	vertices.push_back(topLeftVert);
	vertices.push_back(bottomLeftVert);
	vertices.push_back(topRightVert);

	vertices.push_back(bottomRightVert);
	vertices.push_back(topRightVert);
	vertices.push_back(bottomLeftVert);

}


void Entity::setQuadUVs(std::vector<glm::vec2> &UVs)
{


	glm::vec2 topLeftUV = glm::vec2(0.0f, 0.0f);
	glm::vec2 botLeftUV = glm::vec2(0.0f, uvSize.y);
	glm::vec2 topRightUV = glm::vec2(uvSize.x, 0.0f);
	glm::vec2 botRightUV = glm::vec2(uvSize.x, uvSize.y);


	UVs.push_back(topLeftUV);
	UVs.push_back(botLeftUV);
	UVs.push_back(topRightUV);

	UVs.push_back(botRightUV);
	UVs.push_back(topRightUV);
	UVs.push_back(botLeftUV);
}

GLuint Entity::getTextureUVBuffer()
{
	return model->getUVBuffer();
}

glm::vec2 Entity::getTextureUVOffset()
{
	return glm::vec2(0);
}



void Entity::setModel(Model *m)
{
	model = m;

	bb = new BoundingBox(model->getMinPos(), model->getMaxPos());
}

glm::vec3 Entity::getPosition()
{
	return pos;
}

glm::vec3 Entity::getCentrePosition()
{
	return pos + (dimens / 2.f);
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
	entTexture = t;
}

Texture *Entity::getTexture()
{
	return entTexture;
}


glm::mat4 Entity::getModelMatrix()
{

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
	return dimens;
}

BoundingBox *Entity::getBoundingBox()
{
	return bb;
}

void Entity::moveRight(float dt)
{
	pos.x += speed * dt;

	modelMatChanged = true;
}

void Entity::moveLeft(float dt)
{
	pos.x -= speed * dt;

	modelMatChanged = true;
}

void Entity::moveDown(float dt)
{
	pos.y += speed * dt;

	modelMatChanged = true;
}

void Entity::moveUp(float dt)
{
	pos.y -= speed * dt;

	modelMatChanged = true;
}


float Entity::getRoll()
{
	return rotRoll;
}
