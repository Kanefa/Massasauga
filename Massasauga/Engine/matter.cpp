#include "matter.h"

Matter::Matter() : m_millisecondsPerSecond(1000.0)
{
	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = 0;
	m_rect.h = 0;
}

bool Matter::IsCollision(SDL_Rect rect) const
{
	//The sides of the rectangles
	int leftRect0, leftRect1;
	int rightRect0, rightRect1;
	int topRect0, topRect1;
	int bottomRect0, bottomRect1;

	//Calculates the sides of *this rect
	leftRect0 = m_rect.x;
	rightRect0 = m_rect.x + m_rect.w;
	topRect0 = m_rect.y;
	bottomRect0 = m_rect.y + m_rect.h;

	//Calculates the sides of another object's rect
	leftRect1 = rect.x;
	rightRect1 = rect.x + rect.w;
	topRect1 = rect.y;
	bottomRect1 = rect.y + rect.h;

    if( bottomRect0 <= topRect1 )
    {
        return false;
    }
    
    if( topRect0 >= bottomRect1 )
    {
        return false;
    }
    
    if( rightRect0 <= leftRect1 )
    {
        return false;
    }
    
    if( leftRect0 >= rightRect1 )
    {
        return false;
    }
    
    return true;
}