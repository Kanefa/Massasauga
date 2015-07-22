#ifndef GLOBALS_H
#define GLOBALS_H

#include "keyboard.h"
#include "FrameRateRegulator.h"
#include "../Game/game.h"
#include "SDL.h"

// alw - 6/10/10 - Using the Singleton design pattern
// Modern C++ Design: Generic Programming and Design Patterns Applied
class Globals
{
public:
	static Globals* Instance();
	int getQuit() const {return m_quit;}
	void setQuit(bool quit) {m_quit = quit;}
	SDL_Event& getEvent() {return m_event;}
	Keyboard& getKeyboard() {return m_keyboard;}
	Game& getGame() {return m_game;}
	FrameRateRegulator& GetFrameRateRegulator() {return m_frameRateRegulator;}

private:
	Globals();								// available only to members and friends
	~Globals();								// prevents others from deleting our single instance
	Globals(const Globals &);				// disallow copy constructor
	Globals & operator=(const Globals &);	// disallow assignment operator
	static Globals* pInstance_;

	bool m_quit;
	SDL_Event m_event;
	Keyboard m_keyboard;
	Game m_game;
	FrameRateRegulator m_frameRateRegulator;
};
#endif
