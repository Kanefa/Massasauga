#ifndef MAP_H
#define MAP_H

#include "tile.h"
#include "TinyXML\tinyxml.h"
#include <vector>

class Map
{
public:
	Map();
	Map(std::string mapName, int mapWidth, int mapHeight, int totalTiles);
	Map & operator=(const Map &);
	void Show();
	bool IsTilePassable(const SDL_Rect& rect) const;
	int GetMapWidth() const {return m_mapWidth;}
	int GetMapHeight() const {return m_mapHeight;}
	const SDL_Rect& GetClip(int index) const;
	const std::vector<int>& GetImpassableTileTypes() const {return m_impassableTileTypes;}


private:
	Map(const Map &); // disallow copy constructor
	void LoadTextures();
	bool ReadMap(std::string fileName);
	bool ReadXML();
	bool IsPassable(int tileType) const;

	std::string m_mapName;
	int m_mapWidth;
	int m_mapHeight;
	int m_totalTiles;
	std::string m_imageFile;
	std::vector<SDL_Rect> m_clips; //The portions of the sprite map to be blitted
	std::vector<Image> m_images;
	std::vector<int> m_impassableTileTypes; //All tile types that are impassable (defined by MapConfig.xml)
	std::vector<Tile*> m_tileMap;
};
#endif