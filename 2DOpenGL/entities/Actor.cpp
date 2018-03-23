#include "Actor.h"

Actor::Actor(Texture* entTexture, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : WorldObject(entTexture, pos, dimens, uvSize)
{
	actorInit();
}


Actor::Actor(glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : WorldObject(pos, dimens, uvSize, offPos, container)
{
	actorInit();
}

Actor::~Actor()
{

}

void Actor::actorInit()
{
	onFloor = false;

	fHBMatrix = glm::mat4(1);

	acceleration = glm::vec3(0, 500.1f, 0);


	float floorHBHalfHeight = 0.01;

	glm::vec3 ogFloorPos = glm::vec3(-offsetPos.x, -offsetPos.y - floorHBHalfHeight, 0);
	glm::vec3 ogFloorMaxPos = glm::vec3(-offsetPos.x, -offsetPos.y + floorHBHalfHeight, 0);


	floorHitBox = new BoundingBox(-ogFloorPos, ogFloorMaxPos);
	fHBPos = glm::vec3(pos.x, pos.y + dimens.y, 0);

	maxXVel = 200.f;


	staticFriction = 0.5;
	dynamicFriction = 0.2;

	moving = false;
	speed = 500;
	airSpeed = 350;

	drag = 75.f;
}


void Actor::update(float dt)
{
	WorldObject::update(dt);

	if (!moving)
	{
		if (velocity.x < 1 &&
			velocity.x > -1)
		{
			velocity.x = 0;
		}
	}
	

	if (velocity.y < 0.01 &&
		velocity.y > -0.01)
	{
		velocity.y = 0;
	}



	if (!onFloor && !moving)
	{
		if (velocity.x > 0)
		{
			velocity.x -= drag*dt;
			if (velocity.x < 0)
			{
				velocity.x = 0;
			}
		}
		else {
			velocity.x += drag*dt;
			if(velocity.x > 0)
			{
				velocity.x = 0;
			}
		}
		
	}


	

	fHBPos = pos + fHBPos;
	updateFloorHitBox();


	
	
}

void Actor::updateFloorHitBox()
{

	glm::mat4 m = glm::mat4(1.0);

	glm::vec3 jointPos = pos + offsetPos + fHBPos;



	


	//translate to new position
	//use joint position as this is for rendering
	m = glm::translate(m, jointPos);

	//rotate x
	m = glm::rotate(m, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	m = glm::rotate(m, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	m = glm::rotate(m, rotRoll, glm::vec3(0, 0, 1));

	//scale
	m = glm::scale(m, modScale);


	fHBMatrix = m;
}

void Actor::moveRight(float dt)
{
	if (onFloor)
	{
		velocity.x += speed  *dt;
	}
	else {
		velocity.x += airSpeed * dt;
	}

	moving = true;

	modelMatChanged = true;
}

void Actor::moveLeft(float dt)
{
	if (onFloor)
	{
		velocity.x -= speed *dt;
	}
	else {
		velocity.x -= airSpeed *dt;

	}
	
	/*if (velocity.x < -speed) {
	velocity.x = -speed;
	}*/


	moving = true;
	modelMatChanged = true;
}

void Actor::moveDown(float dt)
{
	acceleration.y += speed * dt;

	modelMatChanged = true;
}

void Actor::moveUp(float dt)
{
	acceleration.y -= speed * dt;

	modelMatChanged = true;
}


void Actor::jump(float dt)
{
	velocity.y -= 260.f;
	printf("Jump\n");
}

void Actor::hitTile(glm::vec3 colNorm, glm::vec3 tangent, glm::vec3 frictionVel, float dt)
{
	


	glm::vec3 normV = velocity * colNorm;

	glm::vec3 dtFriction = frictionVel *dt;



	//printf("Current velocity X: %f \n", velocity.x);
//	printf("Velocity X friction wants to take: %f \n", frictionVel.x);

	float tmpAccelX = 0;

	if (colNorm.x > 0)
	{
		velocity.x -= normV.x;
	}
	else {
		velocity.x += normV.x;
	}
	
	if (colNorm.y > 0)
	{
		velocity.y -= normV.y;
	}
	else {
		velocity.y += normV.y;
	}
}



void Actor::hitTileFriction(glm::vec3 tangent, glm::vec3 frictionVel, float dt)
{

	glm::vec3 dtFriction = frictionVel  *dt;


	float tmpAccelX = 0;
	if (!moving)
	{

		if (tangent.x > 0)
		{
			tmpAccelX -= dtFriction.x;
			velocity.x += tmpAccelX;
			if (velocity.x < 0)
			{
				velocity.x = 0;
			}

		}
		else {
			tmpAccelX -= dtFriction.x;
			velocity.x -= tmpAccelX;
			if (velocity.x > 0)
			{
				velocity.x = 0;
			}
		}
	}


}
