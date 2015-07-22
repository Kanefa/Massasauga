#ifndef BOULDERROCK_H
#define BOULDERROCK_H

#include "gameState.h"
#include "../../Engine/map.h"
#include "../Enemy/bandit.h"
#include "SDL.h"

class BoulderRock : public GameState
{
public:
	BoulderRock();
	void HandleEvents();
    void Logic();
    void Render();
	~BoulderRock();

	Map& getMap() {return m_map;}

private:
	BoulderRock(const BoulderRock &); //Disallow copy constructor
	BoulderRock & operator=(const BoulderRock &); //Disallow assignment operator
	Map m_map;
	SDL_Rect m_boulderRockExit;
	std::vector<Enemy*> m_enemies;
};
#endif