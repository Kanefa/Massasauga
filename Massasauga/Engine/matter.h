#ifndef MATTER_H
#define MATTER_H

#include "SDL.h"

//All visible "objects" in game will be derived from this class.  Therefore, I picked the name matter because
//"Matter is a general term for the substance of which all physical objects are made."  Will I regret this class
//name in the future?  Probably.

class Matter
{
public:
	Matter();
	virtual void Show() = 0;
	bool IsCollision(SDL_Rect rect) const;
	const SDL_Rect& GetRect() const {return m_rect;}

protected:
	const double m_millisecondsPerSecond;
	SDL_Rect m_rect;

private:
	Matter(const Matter &); // disallow copy constructor
	Matter & operator=(const Matter &); // disallow assignment operator
};
#endif