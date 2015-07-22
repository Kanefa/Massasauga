#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "../Engine/map.h"
#include "SDL.h"

class Game
{
//All game specific code globals
public:
	Game();
	SDL_Rect& getCamera() {return m_camera;}
    Player& getPlayer1() {return m_player1;}
	const Map& GetMap() const {return m_map;}
	void SetMap(const Map& map);

private:
	Game(const Game &); // disallow copy constructor
	Game & operator=(const Game &); // disallow assignment operator
	SDL_Rect m_camera;
	Player m_player1;
	Map m_map;
};
#endif