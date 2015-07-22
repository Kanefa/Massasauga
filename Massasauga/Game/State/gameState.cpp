#include "gameState.h"
#include "titleScreen.h"
#include "overWorld.h"
#include "boulderRock.h"

//State variables
int stateID = STATE_NULL;
int nextState = STATE_NULL;

//Game state object
GameState* currentState = NULL;

void SetNextState( int newState )
{
    //If the user doesn't want to exit
    if( nextState != STATE_EXIT )
    {
        //Set the next state
        nextState = newState;
    }
}

void ChangeState()
{
    //If the state needs to be changed
    if( nextState != STATE_NULL )
    {
        //Delete the current state
        if( nextState != STATE_EXIT )
        {
            delete currentState;
        }

        //Change the state
        switch( nextState )
        {
            case STATE_TITLE_SCREEN:
			{
				currentState = new TitleScreen();
				break;
			}
            case STATE_OVER_WORLD:
			{
                currentState = new OverWorld(stateID);
				break;
			}
            case STATE_BOULDER_ROCK:
			{
                currentState = new BoulderRock();
				break;
			}
        }
        
        //Change the current state ID
        stateID = nextState;
        
        //NULL the next state ID
        nextState = STATE_NULL;    
    }
}