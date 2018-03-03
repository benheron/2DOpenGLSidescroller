#include "ResourceManager.h"

ResourceManager::ResourceManager(KeyboardManager *km) : km(km)
{
	initResources();
}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::initResources()
{
	timg = new TextImageManager("res/fonts/fontarial.txt");


}

TextImageManager* ResourceManager::getTextImageManager()
{
	return timg;
}




KeyboardManager* ResourceManager::getKeyboardManager()
{
	return km;
}