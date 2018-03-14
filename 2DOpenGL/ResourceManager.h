#pragma once
#include "text/TextImageManager.h"
#include "levelManagement/TileTypeManager.h"
#include "levelManagement/MapManager.h"

#include "Keyboard.h"

class ResourceManager
{
public:
	ResourceManager(KeyboardManager *km);
	~ResourceManager();

	void initResources();


	TextImageManager* getTextImageManager();

	KeyboardManager* getKeyboardManager();

	TileTypeManager* getTileTypeManager();

	MapManager* getMapManager();



protected:

	TileTypeManager* ttmng;
	TextImageManager* timg;
	KeyboardManager* km;
	MapManager* mmng;

};