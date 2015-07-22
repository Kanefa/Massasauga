#include "game.h"
#include "../Engine/screen.h"

Game::Game() : m_player1("player1")
{
	m_camera.x = 0;
	m_camera.y = 0;
	m_camera.w = Screen::Instance()->getScreenWidth();
	m_camera.h = Screen::Instance()->getScreenHeight();
}

void Game::SetMap(const Map& map)
{
	m_map = map;
}
