#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstdio>

enum eGameStates
{
	STATE_NULL,
	STATE_TITLE_SCREEN,
	STATE_OVER_WORLD,
	STATE_BOULDER_ROCK,
	STATE_EXIT,
};

extern int stateID; //State variables
extern int nextState; //State variables

class GameState;
extern GameState* currentState; //Game state object

void SetNextState( int newState ); //State status manager
void ChangeState(); //State changer

class GameState
{
public:
	GameState(){};
	virtual void HandleEvents() = 0;
    virtual void Logic() = 0;
    virtual void Render() = 0;
    virtual ~GameState(){};

private:
	GameState(const GameState &); //Disallow copy constructor
	GameState & operator=(const GameState &); //Disallow assignment operator
};
#endif