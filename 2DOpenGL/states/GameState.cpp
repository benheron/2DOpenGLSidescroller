#include "GameState.h"
#include "GameOverState.h"

GameState::GameState(StateManager* manager, Platform *platform, ResourceManager* rm) : State(manager, platform), rm(rm)
{
	km = rm->getKeyboardManager();
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
	if (km->keyDown("a"))
	{
		e1->moveLeft(dt);
	}

	if (km->keyDown("d"))
	{
		e1->moveRight(dt);
	}

	if (km->keyDown("w"))
	{
		e1->moveUp(dt);
	}

	if (km->keyDown("s"))
	{
		e1->moveDown(dt);
	}

	if (km->keyDown("right"))
	{
		e1->setRoll(2 * dt, 1);
	}

	if (km->keyDown("left"))
	{
		e1->setRoll(-2 * dt, 1);
	}

	//camera->setPosition(e1->getCentrePosition() * glm::vec3(-1), false);
	//camera->setPosition(glm::vec3(platform->getWindowSize() / 2.f * glm::vec2(1), 0), true);

	for (int i = 0; i < entities.size(); i++)
	{
		//printf("%i\n", i);
		entities[i]->update(dt);



		bool playerCollidedWithTile = mn->collideWithTile(e1);
	}

}


void GameState::load()
{

	


	mn = new MapRoom(rm->getMapManager(), rm->getTileTypeManager(), "M01");
 
	entities.push_back(mn);

	std::vector<Entity*> mnb = mn->getTilesEntities("B");
	std::vector<Entity*> mno = mn->getTilesEntities("O");

	//entities.insert(std::end(entities), std::begin(mnb), std::end(mnb));
	//entities.insert(std::end(entities), std::begin(mno), std::end(mno));
	


	glm::vec3 entPos = glm::vec3(0, 0, 0);
	//glm::vec3 entDimens = glm::vec3(0, 0, 0);
	Texture* t1 = new Texture("res/img/movplat.png");
	e1 = new Entity(t1, entPos);

	//e1->setPosition(glm::vec3(500, 730, 0));

	entities.push_back(e1);
	

}

void GameState::unload()
{

}