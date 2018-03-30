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
		hasMoved = true;
		postVel = false;
	}

	if (km->keyDown("d"))
	{
		e1->moveRight(dt);
		hasMoved = true;
		postVel = false;
	}

	if (km->keyDown("w"))
	{
		if (e1->getOnFloor())
		{
			e1->jump(dt);
		}

		//e1->moveUp(dt);
	}

	if (km->keyDown("s"))
	{
		//e1->moveDown(dt);
	}

	if (km->keyDown("right"))
	{
		e1->setRoll(2 * dt, 1);
		
	}

	if (km->keyDown("left"))
	{
		e1->setRoll(-2 * dt, 1);
		
	}


	if (km->keyDown("up"))
	{
		camera->setScale(glm::vec3(2.f*dt, 2.f*dt, 0), true);

	}

	if (km->keyDown("down"))
	{
		camera->setScale(glm::vec3(-2.f*dt, -2.f*dt, 0), true);

	}

	if (!km->keyDown("a") &&
		!km->keyDown("d"))
	{
		e1->setMoving(false);
		
	}

	if (km->keyDown("k"))
	{
		cameraFollow = !cameraFollow;
	}

	if (!e1->getMoving() && e1->getOnFloor() && hasMoved)
	{
		if (!postVel)
		{
			speedWhenStopped = e1->getVelocity().x;
			postVel = true;
		}



		if (e1->getVelocity().x > 0 ||
			e1->getVelocity().x < 0)
		{
			timings += dt;
		}
		else {
			printf("Time to stop: %f \n", timings);
			printf("Player x velocity: %f \n", speedWhenStopped);
			timings = 0;
			hasMoved = false;
		}
	}




	e1->update(dt);

	


	
	

	

	for (int i = 0; i < entities.size(); i++)
	{
		//printf("%i\n", i);
		//entities[i]->update(dt);



	


	}
	bool playerCollidedWithTile = mn->collideWithTile(e1, dt);

	//printf("Has collided %s \n", playerCollidedWithTile ? "True" : "False");

	if (!playerCollidedWithTile)
	{
		int f = 0;
		//printf("Player feet position y: %f after collision \n", (e1->getPosition().y + e1->getDimensions().y));
	}
	if (cameraFollow)
	{
		//camera->setPosition(e1->getCentrePosition() * glm::vec3(-1.f), false);
		//camera->setPosition(glm::vec3(platform->getRenderSize() / 2.f, 0), true);


		glm::vec3 camPos = (e1->getCentrePosition()) - glm::vec3(platform->getRenderSize() / 2.f, 0);
		glm::vec2 camDim = camera->getDimensions();

		//printf("Camera dimensions: X: %f, Y: %f \n", camDim.x, camDim.y);


		if (camPos.x < 0)
		{
			camPos.x = 0;
		}
		if ((camPos.x + camDim.x) > mn->getDimensions().x )
		{
			camPos.x = mn->getDimensions().x - camDim.x;
		}


		if (camPos.y < 0)
		{
			camPos.y = 0;
		}
		if ((camPos.y + camDim.y) > mn->getDimensions().y)
		{
			camPos.y = mn->getDimensions().y - camDim.y;
			
		}
		camPos *= glm::vec3(-1.f) ;

		camera->setPosition(camPos);



		//camera->setOrigin(e1->getCentrePosition() * glm::vec3(-1.f));
		//printf("Camera position x: %f, y: %f \n", camera->getPosition().x, camera->getPosition().y);


		camPos = glm::vec3(round(camPos.x), round(camPos.y), 0);


		bg->update(dt, camPos);

	}

	//glm::vec3 cameraChange = e1->getCentrePosition() * glm::vec3(-1) + glm::vec3(platform->getWindowSize() / 2.f, 0);







	if (km->keyDown("r"))
	{
		e1->setPosition(glm::vec3(500, 730, 0));
		e1->setVelocity(glm::vec3(0), false);
		e1->setRoll(0, false);
	}

	

	if (km->keyDown("l"))
	{
		//printf("Player x velocity: %f \n", e1->getVelocity().x);
	}
	

}


void GameState::load()
{
	//debug vars
	timings = 0;
	hasMoved = false;
	lastVel = 0;
	
	camera->setDimensions(platform->getRenderSize());



	


	mn = new MapRoom(rm->getMapManager(), rm->getTileTypeManager(), "M01");
 

	bg = new Background(rm->getBackgroundManager()->getBackgroundsByID("Grassland"), mn->getDimensions());

	entities.push_back(bg);
	entities.push_back(mn);

	std::vector<Entity*> mnb = mn->getTilesEntities("B");
	std::vector<Entity*> mno = mn->getTilesEntities("O");

	//entities.insert(std::end(entities), std::begin(mnb), std::end(mnb));
	//entities.insert(std::end(entities), std::begin(mno), std::end(mno));
	


	glm::vec3 entPos = glm::vec3(0, 0, 0);
	//glm::vec3 entDimens = glm::vec3(0, 0, 0);
	Texture* t1 = new Texture("res/img/gingman2.png");
	e1 = new Actor(rm->getSpriteSheetManager()->getSpriteSheetByID("Gingerman"), entPos, glm::vec3(20,32,0));

	e1->setPosition(glm::vec3(500, 730, 0));
	//e1->setRoll(Collision::PI/2, false);

	entities.push_back(e1);
	

}

void GameState::unload()
{
	delete player;
	delete mn;
}