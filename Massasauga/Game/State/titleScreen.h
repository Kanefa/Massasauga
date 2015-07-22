#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "gameState.h"
#include "../../Engine/text.h"

class TitleScreen : public GameState
{
public:
	TitleScreen();
	void HandleEvents();
    void Logic();
    void Render();
	~TitleScreen();

private:
	TitleScreen(const TitleScreen &){}; //Disallow copy constructor
	TitleScreen & operator=(const TitleScreen &){}; //Disallow assignment operator
	Text m_title;
	Text m_pressEnter;
};
#endif