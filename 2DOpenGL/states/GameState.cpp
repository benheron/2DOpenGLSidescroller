#include "GameState.h"
#include "GameOverState.h"

GameState::GameState(StateManager* manager, Platform *platform, ResourceManager* rm) : State(manager, platform), rm(rm)
{

}

GameState::~GameState()
{
	
}

bool GameState::eventHandler()
{
	return false;
}

void GameState::update(float dt)
{
	

}


void GameState::load()
{

	glm::vec3 entPos = glm::vec3(0, 0, 0);
	Entity* e1 = new Entity(entPos);
	Texture* t1 = new Texture();
	t1->loadTexture("res/img/box.png");
	e1->setTexture(t1);

	e1->setPosition(glm::vec3(50, 50, 0), false);

	entities.push_back(e1);
}

void GameState::unload()
{

}