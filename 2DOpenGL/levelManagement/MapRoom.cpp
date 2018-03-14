#include "MapRoom.h"

MapRoom::MapRoom()
{
	
}

MapRoom::MapRoom(MapManager *mpmng, TileTypeManager *ttmng, std::string id) : Entity(glm::vec3(0), glm::vec3(0), glm::vec2(0), ttmng->getTileTypeSize() / 2.f, true)
{


	RoomTemplate *rt = mpmng->getMap(id);
	roomTiles = rt->getRoomTiles();

	layerIDs = rt->getLayerIDs();
	//roomPos = pos;

	roomTilesStrings = rt->getRoomTileData();


	exists = true;

	

	createRoom(mpmng, ttmng);
}


MapRoom::~MapRoom()
{

	for (int i = 0; i < layerIDs.size(); i++)
	{
		//Store the ID of the layer
		std::string layerID = layerIDs[i];


		int ySize = roomTiles["B"].size();



		for (int y = 0; y < ySize; y++)
		{
			int xSize = roomTiles["B"][0].size();

			if (layerID == "O" || layerID == "B")
			{

				for (int x = 0; x < xSize; x++)
				{
					delete roomTiles[layerID][y][x];
				}
			}
		}
	}





}


//this one
void MapRoom::createRoom(MapManager *mpmng, TileTypeManager *ttmng)
{
	//generate new room from the template data
	//this allows the same room to be used but hold different data incase some is changed mid-gameplay

	


	//temp
	ttm = ttmng;

	int numLayers = layerIDs.size();

	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomys;
	std::vector<std::string> creatureys;

	int c = 0;

	for (int i = 0; i < numLayers; i++)
	{
		std::vector<glm::vec2> verts;
		std::vector<glm::vec2> us;


		//Store the ID of the layer
		std::string layerID = layerIDs[i];


		int ySize = roomTilesStrings["B"].size();

		int zVal;


		for (int y = 0; y < ySize; y++)
		{
			int xSize = roomTilesStrings["B"][0].size();

			if (layerID == "O" || layerID == "B")
			{
				std::vector<Tile*> tiles;
				roomTiles[layerID].push_back(tiles);

				for (int x = 0; x < xSize; x++)
				{
					//Get the tile
					std::string tileID = roomTilesStrings[layerID][y][x];

					if (tileID != "XX")
					{
						//Get the data to load into the new tile
						TileType* tileType = ttmng->getTileType(tileID);

						Tile *t = new Tile(glm::vec3((x * 32), (y * 32), 0), glm::vec3(32, 32, 0), tileType);

						std::vector<glm::vec2> v = t->getEntityVertices();
						std::vector<glm::vec2> u = t->getEntityUVs();

						verts.insert(std::end(verts), std::begin(v), std::end(v));
						us.insert(std::end(us), std::begin(u), std::end(u));

						if (!t->haveBlankID() && !t->getClimbable())
						{

							t->setSideL(true);
							t->setSideR(true);
							t->setSideU(true);
							t->setSideD(true);
						}


						if (t->getTileTypeID() == "L2")
						{
							t->setSideU(true);
						}

						roomTiles[layerID][y].push_back(t);
					}
				}
			}

		}
		if (verts.size() > 0)
		{
			Model * mo = new Model(verts, us);

			entModels.push_back(mo);

			entTextures.push_back(ttmng->getTileTypeTexture(layerID));
			
		}
		

	}

	labelTileSides();

	
	
	//player = new Character(playerSpawn, cmng->getCharacterType("G1"));

	//player->setGravityOn(true);

}

void MapRoom::labelTileSides()
{
	std::vector<std::vector<Tile*>> objectLayerTiles = roomTiles["O"];
	int h = objectLayerTiles.size();
	int l = objectLayerTiles[0].size();

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < l; j++)
		{

			Tile *thisTile = objectLayerTiles[i][j];

			int befX = j - 1;
			int befY = i - 1;
			int afX = j + 1;
			int afY = i + 1;
			

			/*if (befX > -1 && befY > -1 &&
				afX < l && afY < h)*/
			{
				if (!thisTile->haveBlankID() || !thisTile->getCollidable())
				{
					if (befX > -1)
					{
						//check left side
						if (thisTile->getSideL() && objectLayerTiles[i][j - 1]->getSideR())
						{
							thisTile->setSideL(false);
							objectLayerTiles[i][j - 1]->setSideR(false);
						}
					}
					
					if (afX < l)
					{
						//check right side
						if (thisTile->getSideR() && objectLayerTiles[i][j + 1]->getSideL())
						{
							thisTile->setSideR(false);
							objectLayerTiles[i][j + 1]->setSideL(false);
						}
					}
					
					if (befY < -1)
					{
						//check above
						if (thisTile->getSideU() && objectLayerTiles[i - 1][j]->getSideD())
						{
							thisTile->setSideU(false);
							objectLayerTiles[i - 1][j]->setSideD(false);
						}
					}
				
					
					if (afY < h)
					{
						//check below
						if (thisTile->getSideD() && objectLayerTiles[i + 1][j]->getSideU())
						{
							thisTile->setSideD(false);
							objectLayerTiles[i + 1][j]->setSideU(false);
						}
					}
					
				}
			}
		}
	}
}



/*
void MapRoom::update(float dt)
{
	
	
}
*/



void MapRoom::setPos(glm::vec2 pos)
{
	roomPos = pos;
}

glm::vec2 MapRoom::getPos()
{
	return roomPos;
}



void MapRoom::setExists(bool e)
{
	exists = e;
}

bool MapRoom::getExists()
{
	return exists;
}

std::vector<Entity*> MapRoom::getTilesEntities(std::string layer)
{
	std::vector<Entity*> tmp;

	for (int i = 0; i < roomTiles[layer].size(); i++)
	{
		for (int j = 0; j < roomTiles[layer][i].size(); j++)
		{
			if (!roomTiles[layer][i][j]->haveBlankID())
			{
				tmp.push_back(roomTiles[layer][i][j]);
			}
			
		}
	}


	return tmp;
}



Tile* MapRoom::getTile(glm::vec2 xy)
{
	return roomTiles["O"][xy.y][xy.x];
}



void MapRoom::changeTileType(std::string layer, glm::vec2 tilePos, std::string tileID, TileTypeManager *ttmng)
{
	if (layer == "O" || layer == "B")
	{
		roomTiles[layer][tilePos.y][tilePos.x]->setTileType(tileID, ttmng);
		roomTilesStrings[layer][tilePos.y][tilePos.x] = tileID;
	}
	
}



std::unordered_map<std::string, std::vector<std::vector<std::string>>> MapRoom::getRoomTilesStrings()
{
	return roomTilesStrings;
}


std::vector<std::string> MapRoom::getLayerIDs()
{
	return layerIDs;
}
