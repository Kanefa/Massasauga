#include "Engine/init.h"
#include "Engine/screen.h"
#include "Engine/globals.h"
#include "Game/State/gameState.h"
#include "Game/State/titleScreen.h"

/*
Opitmized surface loading and blitting - image.cpp
Color keying - image.cpp
Clip Blitting and Sprite Sheets

Design Patterns in use
Singleton
*/
	
int main( int argc, char* args[] )
{
	Init init;

	stateID = STATE_TITLE_SCREEN;
	currentState = new TitleScreen();

    //While the user hasn't quit
    while( stateID != STATE_EXIT )
    {
        //Start the frame timer
		Globals::Instance()->GetFrameRateRegulator().Update();
        
        //Do state event handling
		currentState->HandleEvents();
        
        //Do state logic
        currentState->Logic();
        
        //Change state if needed
		ChangeState();
        
        //Clear screen
		glClear( GL_COLOR_BUFFER_BIT );

		//Do state rendering
        currentState->Render();

		//Display FPS
		Globals::Instance()->GetFrameRateRegulator().DisplayFrameRate();
        
        //Update the screen
		SDL_GL_SwapBuffers();

		//Cap framerate
		Globals::Instance()->GetFrameRateRegulator().CapFrameRate();
    }

	SDL_Quit();
    return 0;
}