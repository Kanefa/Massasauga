#include "titleScreen.h"
#include "../../Engine/globals.h"
#include <string>

TitleScreen::TitleScreen() : m_title("Title Screen", "fonts\\arial.ttf", 32, 100, 100, 255), m_pressEnter("Press [Enter] to continue.", "fonts\\arial.ttf", 28, 255, 255, 255)
{
}

void TitleScreen::HandleEvents()
{
    //While there's events to handle
    while( SDL_PollEvent( &Globals::Instance()->getEvent() ) )
    {
        //If the user has Xed out the window
        if( Globals::Instance()->getEvent().type == SDL_QUIT )
        {
            //Quit the program
            SetNextState( STATE_EXIT );
        }
        //If the user pressed enter
        else if( ( Globals::Instance()->getEvent().type == SDL_KEYDOWN ) && ( Globals::Instance()->getEvent().key.keysym.sym == SDLK_RETURN ) )
        {
            //Move to the title screen
            SetNextState( STATE_OVER_WORLD );
        }
    }
}

void TitleScreen::Logic()
{
}

void TitleScreen::Render()
{
	m_title.Apply(380, 200);
	m_pressEnter.Apply(320, 250);
}

TitleScreen::~TitleScreen()
{
}