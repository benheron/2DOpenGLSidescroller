#pragma once
#include "WorldObject.h"
#include "../Animation/SpriteSheet.h"
#include  "../Animation/Animation.h"

enum ActorState
{
	idleState,
	movingState,
	jumpingState,
	climbingState,
	deadState
};

class Actor : public WorldObject
{
public:
	Actor(SpriteSheet* actorSpriteSheet, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

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

	glm::vec2 getTextureUVOffset();


	void setSpriteSheet(SpriteSheet* s) { actorSpriteSheet = s; }



	BoundingBox* getFloorHitBox() { return floorHitBox; }


	bool getMoving() { return moving; }
	void setMoving(bool m) { moving = m; }



	void setOnFloor(bool f) { onFloor = f; }
	bool getOnFloor() { return onFloor; }

private:
	bool alive;

	bool onFloor;

	BoundingBox *floorHitBox;
	glm::vec3 fHBPos;
	glm::mat4 fHBMatrix;


	float drag;


	bool moving;

	float frictionTimings = 0;

	float airSpeed;


	bool changeAnimation;

	SpriteSheet* actorSpriteSheet;
	Animation* currentAnimation;



	ActorState aState;
	ActorState prevState;
};

