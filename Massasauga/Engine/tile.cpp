#include "tile.h"
#include "globals.h"
#include "image.h"

const int Tile::m_tileWidth = 32;
const int Tile::m_tileHeight = 32;
int Tile::m_totalTileTypes = 0;

Tile::Tile(int x, int y, const int type, Image image) : m_type(type), m_image(image)
{
	Matter::m_rect.x = x;
	Matter::m_rect.y = y;
	Matter::m_rect.w = m_tileWidth;
	Matter::m_rect.h = m_tileHeight;
}

void Tile::Show()
{
	SDL_Rect camera = Globals::Instance()->getGame().getCamera();
    
    if( IsCollision(camera) )
    {
        //The tile is on screen, so draw it
		m_image.ApplyImage(Matter::m_rect.x - camera.x, Matter::m_rect.y - camera.y, m_rect);
    }  
}