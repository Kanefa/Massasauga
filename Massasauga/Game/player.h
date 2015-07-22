#ifndef Player_H
#define Player_H

#include "../Engine/matter.h"
#include "../Engine/image.h"
#include "Enemy/enemy.h"
#include "Combat/combatPlayer.h"
#include "SDL.h"
#include <string>
#include <vector>

class Player : public Matter
{
private:
	enum eDirection;

public:
	Player(std::string playerName);
	void Init(int x, int y, int mapWidth, int mapHeight);
	void Show();
	void DoWork(std::vector<Enemy*>& enemies);

	Combat& GetCombat() {return m_combat;}
	eDirection GetDirection() const {return m_direction;}
	void SetDirection(eDirection direction) {m_direction = direction;}
	void SetMapWidth(const int mapWidth) {m_mapWidth = mapWidth;}
	void SetMapHeight(const int mapHeight) {m_mapHeight = mapHeight;}

private:
	Player(const Player &); // disallow copy constructor
	Player & operator=(const Player &); // disallow assignment operator
	void HandleInput();
	void Move();
	void MoveCamera();
	void Combat(std::vector<Enemy*>& enemies);
	void Animate();
	bool ReadXML();

	const std::string m_playerName;
	const int m_velocity;
	const int m_zeroVelocity;
	std::string m_imageFile;
	int m_clipIndex;
	std::vector<SDL_Rect> m_clips; //The portions of the sprite map to be blitted
	Image m_image;
	CombatPlayer m_combat;
	int m_xVelocity, m_yVelocity;
	eDirection m_direction;
	int m_mapWidth;
	int m_mapHeight;

	enum eDirection
	{
		LEFT,
		UPLEFT,		
		DOWNLEFT,
		RIGHT,
		UPRIGHT,
		DOWNRIGHT
		// Bidirectional enums are active on Y-axis, but preserves X-axis orientation.
	};
};
#endif