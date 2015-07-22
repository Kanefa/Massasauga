#include "boulderRock.h"
#include "../../Engine/globals.h"
#include "../../Engine/text.h"
#include "../../Engine/globals.h"
#include "../../Engine/matter.h"
#include <string>

BoulderRock::BoulderRock() : m_map("boulderRock", 1920, 1280, 2400)
{
	Globals::Instance()->getGame().SetMap(m_map);

	m_boulderRockExit.x = 32;
	m_boulderRockExit.y = 32;
	m_boulderRockExit.w = 32;
	m_boulderRockExit.h = 32;

	Globals::Instance()->getGame().getPlayer1().Init(64, 64, m_map.GetMapWidth(), m_map.GetMapHeight());
}

void BoulderRock::HandleEvents()
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
        else if( ( Globals::Instance()->getEvent().type == SDL_KEYDOWN ) && ( Globals::Instance()->getEvent().key.keysym.sym == SDLK_ESCAPE ) )
        {
            //Move to the title screen
            SetNextState( STATE_TITLE_SCREEN );
        }
		else
		{
			Globals::Instance()->getKeyboard().KeyPress();
		}
    }
}

void BoulderRock::Logic()
{
	if (Globals::Instance()->getGame().getPlayer1().IsCollision(m_boulderRockExit))
	{
		SetNextState( STATE_OVER_WORLD );
	}

	Globals::Instance()->getGame().getPlayer1().DoWork(m_enemies);
}

void BoulderRock::Render()
{
	m_map.Show();
	Globals::Instance()->getGame().getPlayer1().Show();
}

BoulderRock::~BoulderRock()
{
}