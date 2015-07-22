#include "map.h"
#include "screen.h"
#include "image.h"
#include "SDL.h"
#include <fstream>
#include <sstream>
#include <string>


Map::Map()
{
}

Map::Map(std::string mapName, int mapWidth, int mapHeight, int totalTiles) : m_mapName(mapName), m_mapWidth(mapWidth), m_mapHeight(mapHeight), m_totalTiles(totalTiles)
{
	bool success = ReadXML();
	assert(success);

	LoadTextures();

	success = ReadMap("Maps\\" + mapName + ".map");
	assert(success);
}

Map& Map::operator=(const Map &map)
{
	//This gracefully handles self assignment
	if (this == &map) 
	{	
		return *this;
	}

	m_mapName = map.m_mapName;
	m_mapWidth = map.m_mapWidth;
	m_mapHeight = map.m_mapHeight;
	m_totalTiles = map.m_totalTiles;
	m_imageFile = map.m_imageFile;
	m_clips.clear();
	copy(map.m_clips.begin(), map.m_clips.end(), std::back_inserter(m_clips));
	m_images.clear();
	copy(map.m_images.begin(), map.m_images.end(), std::back_inserter(m_images));
	m_impassableTileTypes.clear();
	copy(map.m_impassableTileTypes.begin(), map.m_impassableTileTypes.end(), std::back_inserter(m_impassableTileTypes));
	m_tileMap.clear();
	copy(map.m_tileMap.begin(), map.m_tileMap.end(), std::back_inserter(m_tileMap));

	return *this;
}

void Map::Show()
{
	for ( std::vector<Tile*>::const_iterator tileIter = m_tileMap.begin(); tileIter < m_tileMap.end(); tileIter++ )
	{
		//Show the tiles
		(*tileIter)->Show();
	}
}

bool Map::IsTilePassable(const SDL_Rect& rect) const
{
	const int tileWidth = rect.w;
	const int tileHeight = rect.h;
	const int m_mapWidthInTiles = m_mapWidth / tileWidth;

	//Top Left corner
	int tileIndex = rect.y / tileHeight * m_mapWidthInTiles + rect.x / tileWidth;
	int tileType = m_tileMap.at(tileIndex)->GetType();
	if (!IsPassable(tileType))
	{
		return false;
	}

	//Top Right corner
	tileIndex = rect.y / tileHeight * m_mapWidthInTiles + (rect.x + tileWidth - 1)  / tileWidth;
	tileType = m_tileMap.at(tileIndex)->GetType();
	if (!IsPassable(tileType))
	{
		return false;
	}

	//Bottom Left corner
	tileIndex = (rect.y + tileHeight - 1) / tileHeight * m_mapWidthInTiles + rect.x / tileWidth;
	tileType = m_tileMap.at(tileIndex)->GetType();
	if (!IsPassable(tileType))
	{
		return false;
	}

	//Bottom Right corner
	tileIndex = (rect.y + tileHeight - 1) / tileHeight * m_mapWidthInTiles + (rect.x + tileWidth - 1) / tileWidth;
	tileType = m_tileMap.at(tileIndex)->GetType();
	if (!IsPassable(tileType))
	{
		return false;
	}

	return true;
}

const SDL_Rect& Map::GetClip(int index) const
{
	return m_clips.at(index);
}

void Map::LoadTextures()
{
	for ( std::vector<SDL_Rect>::const_iterator clipIter = m_clips.begin(); clipIter < m_clips.end(); clipIter++ )
	{
		m_images.push_back(Image(m_imageFile, *clipIter));
	}
}

bool Map::ReadMap(std::string fileName)
{
	m_tileMap.resize(m_totalTiles);

    //The tile offsets
    int x = 0, y = 0;
    
    //Open the map
	std::ifstream map( fileName.c_str() );
    
    if( !map )
    {
		//The map couldn't be loaded
		return false;
	}

	//Initialize the tiles
	for ( std::vector<Tile*>::iterator tileIter = m_tileMap.begin(); tileIter < m_tileMap.end(); tileIter++ )
	{
		//Determines what kind of tile will be made
		int tileType = -1;
    
		//Read tile from map file
		map >> tileType;
        
		if( map.fail() )
		{
			//There was a problem reading the map
			map.close();
			return false;
		}

		if( ( tileType >= 0 ) && ( tileType < Tile::GetTotalTileTypes() ) )
		{
			//The tileType is a valid tile number
			*tileIter = new Tile( x, y, tileType, m_images.at(tileType) );       
		}
		else 
		{
			//Don't recognize the tile type
			map.close();
			return false;
		}

		//Move to next tile spot
		x += Tile::GetTileWidth();
    
		//If we've gone too far
		if( x >= m_mapWidth )
		{
			//Move back
			x = 0;
            
			//Move to the next row
			y += Tile::GetTileHeight(); 
		}
	}
		
	//Close the file
	map.close();
	return true;
}

bool Map::ReadXML()
{
	TiXmlDocument config( "Configs\\MapConfig.xml" );
	
	if ( !config.LoadFile() )
	{
		return false;
	}

	TiXmlNode* node = config.FirstChild("mapList")->FirstChild("map");
	if (!node)
	{
		return false;
	}

	while (m_mapName.compare(node->ToElement()->Attribute("instance")) != 0)
	{
		//Map name not a match.  Keep looking.
		node = node->NextSibling();
		if (!node)
		{
			//Searched all map names.  No match found.
			return false;
		}
	}

	node = node->FirstChild("image");
	if (!node)
	{
		return false;
	}

	std::stringstream iss (node->ToElement()->GetText());
	iss >> m_imageFile;
	iss.str(""); iss.clear();

	int attributeNumber = 0;
	iss << "x" << attributeNumber;
	std::string attributeString = iss.str();
	iss.str(""); iss.clear();
	int attributeValue = 0;
	
	SDL_Rect tempRect;
	while (node->NextSiblingElement("rects")->QueryIntAttribute(attributeString.c_str(), &attributeValue) == TIXML_SUCCESS)
	{
		iss << attributeValue;
		iss >> tempRect.x;
		iss.str(""); iss.clear();

		iss << "y" << attributeNumber;
		attributeString = iss.str();
		iss.str(""); iss.clear();
		iss << node->NextSiblingElement("rects")->Attribute(attributeString.c_str());
		iss >> tempRect.y;
		iss.str(""); iss.clear();

		iss << "w" << attributeNumber;
		attributeString = iss.str();
		iss.str(""); iss.clear();
		iss << node->NextSiblingElement("rects")->Attribute(attributeString.c_str());
		iss >> tempRect.w;
		iss.str(""); iss.clear();

		iss << "h" << attributeNumber;
		attributeString = iss.str();
		iss.str(""); iss.clear();
		iss << node->NextSiblingElement("rects")->Attribute(attributeString.c_str());
		iss >> tempRect.h;
		iss.str(""); iss.clear();

		m_clips.push_back(tempRect);
		
		iss << "passable" << attributeNumber;
		attributeString = iss.str();
		iss.str(""); iss.clear();
		iss << node->NextSiblingElement("rects")->Attribute(attributeString.c_str());
		std::string passable;
		iss >> passable;
		iss.str(""); iss.clear();
		if (passable.compare("false") == 0)
		{
			m_impassableTileTypes.push_back(attributeNumber);
		}
		passable.clear();

		attributeNumber++;
		iss << "x" << attributeNumber;
		attributeString = iss.str();
		iss.str(""); iss.clear();
	}
	//If m_clips is empty the map has no tiles defined.
	assert(!m_clips.empty());
	Tile::SetTotalTileTypes(m_clips.size());

	return true;
}

bool Map::IsPassable(int tileType) const
{
	std::vector<int>::const_iterator impassableIter;
	for (impassableIter = m_impassableTileTypes.begin(); impassableIter != m_impassableTileTypes.end(); impassableIter++)
	{
		if (tileType == *impassableIter)
		{
			return false;
		}
	}
	return true;
}