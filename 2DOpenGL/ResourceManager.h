#pragma once
#include "text/TextImageManager.h"

#include "Keyboard.h"

class ResourceManager
{
public:
	ResourceManager(KeyboardManager *km);
	~ResourceManager();

	void initResources();


	TextImageManager* getTextImageManager();


	KeyboardManager* getKeyboardManager();



protected:


	TextImageManager* timg;
	KeyboardManager* km;
};