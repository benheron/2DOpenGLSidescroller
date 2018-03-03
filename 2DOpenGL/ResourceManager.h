#pragma once
#include "text/TextImageManager.h"

#include "entities/EntityManager.h"
#include "Keyboard.h"

class ResourceManager
{
public:
	ResourceManager(KeyboardManager *km);
	~ResourceManager();

	void initResources();


	TextImageManager* getTextImageManager();

	EntityManager* getEntityManager();

	KeyboardManager* getKeyboardManager();



protected:


	TextImageManager* timg;
	EntityManager* em;
	KeyboardManager* km;
};