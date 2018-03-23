#pragma once
#include "WorldObject.h"

enum ActorState
{

};

class Actor : public WorldObject
{
public:
	Actor(Texture* entTexture, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	Actor(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);
	~Actor();


	virtual void update(float dt);

	void updateFloorHitBox();

	void actorInit();


	
	void jump(float dt);


	void moveRight(float dt);
	void moveLeft(float dt);

	void moveDown(float dt);
	void moveUp(float dt);

	void hitTile(glm::vec3 colNorm, glm::vec3 tangent, glm::vec3 frictionVel, float dt);

	void hitTileFriction(glm::vec3 tangent, glm::vec3 frictionVel, float dt);





	BoundingBox* getFloorHitBox() { return floorHitBox; }


	bool getMoving() { return moving; }
	void setMoving(bool m) { moving = m; }



	void setOnFloor(bool f) { onFloor = f; }
	bool getOnFloor() { return onFloor; }

private:

	bool onFloor;

	BoundingBox *floorHitBox;
	glm::vec3 fHBPos;
	glm::mat4 fHBMatrix;


	float drag;


	bool moving;

	float frictionTimings = 0;

	float airSpeed;
};

