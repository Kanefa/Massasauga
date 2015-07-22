#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "gameState.h"
#include "../../Engine/map.h"
#include "../Enemy/bandit.h"
#include "SDL.h"

class OverWorld : public GameState
{
public:
	OverWorld(int prevState);
	void HandleEvents();
    void Logic();
    void Render();
	~OverWorld();

	Map& getMap() {return m_map;}

private:
	OverWorld(const OverWorld &); //Disallow copy constructor
	OverWorld & operator=(const OverWorld &); //Disallow assignment operator
	Map m_map;
	SDL_Rect m_boulderRockEntrance;
	std::vector<Enemy*> m_enemies;
};
#endif