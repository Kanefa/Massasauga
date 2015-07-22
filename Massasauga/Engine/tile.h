#ifndef TILE_H
#define TILE_H

#include "matter.h"
#include "image.h"

class Tile : public Matter
{
public:
	Tile(int x, int y, const int type, Image image);
	void Show();
	int GetType() const {return m_type;}
	static int GetTileWidth() {return m_tileWidth;}
	static int GetTileHeight() {return m_tileHeight;}
	static int GetTotalTileTypes() {return m_totalTileTypes;}
	static void SetTotalTileTypes(int totalTileTypes) {m_totalTileTypes = totalTileTypes;}

private:
	Tile(const Tile &); // disallow copy constructor
	Tile & operator=(const Tile &); // disallow assignment operator
	static const int m_tileWidth;
	static const int m_tileHeight;
	static int m_totalTileTypes;
	const int m_type;
	Image m_image;
};
#endif