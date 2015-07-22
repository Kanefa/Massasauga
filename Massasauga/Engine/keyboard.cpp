#include "keyboard.h"
#include "globals.h"

Keyboard::Keyboard()
{
}

void Keyboard::KeyPress()
{
	//If a key was pressed
	if( Globals::Instance()->getEvent().type == SDL_KEYDOWN )
	{
		switch( Globals::Instance()->getEvent().key.keysym.sym )
		{
			case SDLK_UP: m_keyState.isUpPressed = true; break;
			case SDLK_DOWN: m_keyState.isDownPressed = true; break;
			case SDLK_LEFT: m_keyState.isLeftPressed = true; break;
			case SDLK_RIGHT: m_keyState.isRightPressed = true; break;
			case SDLK_SPACE: m_keyState.isSpaceBarPressed = true; break;
		}
	}

	//If a key was released
	if( Globals::Instance()->getEvent().type == SDL_KEYUP )
	{
		switch( Globals::Instance()->getEvent().key.keysym.sym )
		{
			case SDLK_UP: m_keyState.isUpPressed = false; break;
			case SDLK_DOWN: m_keyState.isDownPressed = false; break;
			case SDLK_LEFT: m_keyState.isLeftPressed = false; break;
			case SDLK_RIGHT: m_keyState.isRightPressed = false; break;
			case SDLK_SPACE: m_keyState.isSpaceBarPressed = false; break;
		}
	}
}