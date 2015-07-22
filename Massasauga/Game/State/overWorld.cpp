#include "overWorld.h"
#include "../../Engine/globals.h"
#include "../../Engine/text.h"
#include "../../Engine/globals.h"
#include "../../Engine/matter.h"
#include <string>

OverWorld::OverWorld(int prevState) : m_map("overWorld", 1920, 1280, 2400)
{
	Globals::Instance()->getGame().SetMap(m_map);

	m_boulderRockEntrance.x = 1216;
	m_boulderRockEntrance.y = 608;
	m_boulderRockEntrance.w = 32;
	m_boulderRockEntrance.h = 32;

	m_enemies.push_back(new Bandit(1184,608));
	m_enemies.push_back(new Bandit(1248,544));

	if (prevState == STATE_BOULDER_ROCK)
	{
		Globals::Instance()->getGame().getPlayer1().Init(1184, 608, m_map.GetMapWidth(), m_map.GetMapHeight());
	}
	else
	{
		Globals::Instance()->getGame().getPlayer1().Init(300, 400, m_map.GetMapWidth(), m_map.GetMapHeight());
	}
}

void OverWorld::HandleEvents()
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

void OverWorld::Logic()
{
	if (Globals::Instance()->getGame().getPlayer1().IsCollision(m_boulderRockEntrance))
	{
		SetNextState( STATE_BOULDER_ROCK );
	}

	std::vector<Enemy*>::iterator enemy_iter;
	for(enemy_iter = m_enemies.begin(); enemy_iter != m_enemies.end(); enemy_iter++)
	{
		(*enemy_iter)->DoWork();
	}
	Globals::Instance()->getGame().getPlayer1().DoWork(m_enemies);
}

void OverWorld::Render()
{
	m_map.Show();
	std::vector<Enemy*>::iterator enemy_iter;
	for(enemy_iter = m_enemies.begin(); enemy_iter != m_enemies.end(); enemy_iter++)
	{
		(*enemy_iter)->Show();
	}
	Globals::Instance()->getGame().getPlayer1().Show();
}

OverWorld::~OverWorld()
{
	std::vector<Enemy*>::iterator enemy_iter;
	for(enemy_iter = m_enemies.begin(); enemy_iter != m_enemies.end(); enemy_iter++)
	{
		delete *enemy_iter;
	}
}