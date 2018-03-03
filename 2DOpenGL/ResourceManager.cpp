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
	em = new EntityManager();

}

TextImageManager* ResourceManager::getTextImageManager()
{
	return timg;
}


EntityManager* ResourceManager::getEntityManager()
{
	return em;
}



KeyboardManager* ResourceManager::getKeyboardManager()
{
	return km;
}