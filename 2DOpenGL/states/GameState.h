#pragma once
#include "StateManager.h"
#include "../ResourceManager.h"
#include "../text/Text.h"
#include "../Camera.h"
#include "../Collision.h"
#include "../levelManagement/MapRoom.h"
#include "../entities/Actor.h"
#include "../Background/Background.h"

class GameOverState;

class GameState : public State
{
public:
	GameState(StateManager* manager, Platform *platform, ResourceManager* rm);
	virtual ~GameState();

	/**
	@brief Handles any events such as keyboard/mouse input.

	@return true to exit, false to continue.
	*/
	bool eventHandler();

	/**
	@brief Update any internal values.

	@param dt - delta time.
	*/
	void update(float dt);

	
protected:

	/**
	@brief Loads this State.
	*/
	virtual void load();

	/**
	@brief Unloads this State.
	*/
	virtual void unload();


	bool cameraFollow = true;


	Entity *player;


	MapRoom *mn;


	Background *bg;

	ResourceManager* rm;

	KeyboardManager*km;


	Actor* e1;


	float timings;
	bool hasMoved;

	float lastVel;

	bool postVel = false;
	float speedWhenStopped = 0.f;
	
};