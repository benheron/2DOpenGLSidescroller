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


//	exists = true;

	//explicit tile size
	tileSize = glm::vec2(32, 32);

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

					
					//Get the data to load into the new tile
					TileType* tileType = ttmng->getTileType(tileID);

					Tile *t = new Tile(glm::vec3((x * tileSize.x), (y * tileSize.y), 0), glm::vec3(tileSize.x, tileSize.y, 0), tileType);

					if (tileID == "XX")
					{
						t->setShouldRender(false);
					}

					if (tileID != "XX")
					{
						//get vertices and uvs from tile
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
					}

					roomTiles[layerID][y].push_back(t);
					
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

bool MapRoom::collideWithTile(Entity* e)
{
	glm::vec3 entPos = e->getPosition();
	glm::vec3 entPosDim = entPos + e->getDimensions();

	int minTileX = floor(entPos.x / tileSize.x);
	int minTileY = floor(entPos.y / tileSize.y);


	int maxTileX = floor(entPosDim.x / tileSize.x);
	int maxTileY = floor(entPosDim.y / tileSize.y);

	int xLimit = roomTiles["O"].size() - 1;
	int yLimit = roomTiles["O"][0].size() - 1;

	e->setBlendColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	glm::vec4 blendCol = glm::vec4(1.0f, .0f, .0f, 1.0f);
	

	for (int i = minTileY - 2; i < maxTileY + 2; i++)
	{
		for (int j = minTileX - 2; j < maxTileX + 2; j++)
		{
			if (i > -1 && i < yLimit &&
				j > -1 && j < xLimit)
			{
				Tile* curTile = roomTiles["O"][i][j];
				if (!curTile->haveBlankID())
				{
					//if (Collision::boxBoxCollision(e->getBoundingBox(), curTile->getBoundingBox()))
					if (Collision::SATIntersection(e->getBoundingBox(), curTile->getBoundingBox()))
					{
						e->setBlendColour(blendCol);
						curTile->setBlendColour(blendCol);

						
					}
					
				}
			}
		}
	}


	return true;
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
