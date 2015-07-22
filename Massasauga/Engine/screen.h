#ifndef SCREEN_H
#define SCREEN_H

#include "SDL.h"

// alw - 6/10/10 - Using the Singleton design pattern
// Modern C++ Design: Gneric Programming and Design Patterns Applied
class Screen
{
public:
	static Screen* Instance();
	SDL_Surface* getScreen() const {return m_screen;}
	void setScreen(SDL_Surface *screen) {m_screen = screen;}
	int getScreenWidth() const {return m_screenWidth;}
	int getScreenHeight() const {return m_screenHeight;}
	int getScreenBPP() const {return m_screenBPP;}

private:
	Screen();							// available only to members and friends
	~Screen() {};						// prevents others from deleting our single instance
	Screen(const Screen&);				// disallow copy constructor
	Screen & operator=(const Screen&);	// disallow assignment operator
	static Screen* pInstance_;			// The one and only instance

	//The attributes of the screen
	const int m_screenWidth;
	const int m_screenHeight;
	const int m_screenBPP;
	//The surfaces that will be used
	SDL_Surface *m_screen;
};
#endif