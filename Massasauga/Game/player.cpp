#include "player.h"
#include "../Engine/screen.h"
#include "../Engine/globals.h"
#include "../Engine/misc.h"
#include "../Engine/TinyXML\tinyxml.h"
#include "SDL.h"
#include <sstream>
#include <string>

Player::Player(const std::string playerName) : m_playerName(playerName), m_velocity(400), m_zeroVelocity(0), m_clipIndex(0)
, m_combat(100, 0, 0), m_xVelocity(0), m_yVelocity(0), m_direction(RIGHT), m_mapWidth(0), m_mapHeight(0)
{
	//Read properties from PlayerConfig.xml
	bool success = ReadXML();
	assert(success);

	//Load player sprite
	m_image = Image(m_imageFile, m_clips.at(m_clipIndex));

	//Set width and height
	Matter::m_rect.w = m_clips.at(m_clipIndex).w;
	Matter::m_rect.h = m_clips.at(m_clipIndex).h;
}

void Player::Init(int x, int y, int mapWidth, int mapHeight)
{
	Matter::m_rect.x = x;
	Matter::m_rect.y = y;
	m_mapWidth = mapWidth;
	m_mapHeight = mapHeight;
}

void Player::Show()
{
	m_image.ApplyImage(Matter::m_rect.x - Globals::Instance()->getGame().getCamera().x, Matter::m_rect.y - Globals::Instance()->getGame().getCamera().y, Matter::m_rect );
}

void Player::DoWork(std::vector<Enemy*>& enemies)
{
	HandleInput();
	Move();
	MoveCamera();
	Combat(enemies);
	Animate();
}

void Player::HandleInput()
{
	//Detected cases of phantom key blocking.  For example, Up+Down+Right registered correctly on my 
	//keyboard, but when pressing Up+Down+Left the left key was never detected.  To be consistent I
	//never try to detect more than two directional key presses.

	m_xVelocity = m_zeroVelocity;
	m_yVelocity = m_zeroVelocity;

	if ( Globals::Instance()->getKeyboard().isLeftPressed() && Globals::Instance()->getKeyboard().isRightPressed() )
	{
		m_xVelocity = m_zeroVelocity;
	}
	else
	{
		if ( Globals::Instance()->getKeyboard().isUpPressed() )
		{
			m_yVelocity -= m_velocity;
			switch(GetDirection())
			{
				case LEFT: case UPLEFT: SetDirection(UPLEFT); break;
				case RIGHT: case UPRIGHT: SetDirection(UPRIGHT); break;
			}
		}

		if ( Globals::Instance()->getKeyboard().isDownPressed() )
		{
			m_yVelocity += m_velocity;
			switch(GetDirection())
			{
				case LEFT: case DOWNLEFT: SetDirection(DOWNLEFT); break;
				case RIGHT: case DOWNRIGHT: SetDirection(DOWNRIGHT); break;
			}
		}
	}

	if ( Globals::Instance()->getKeyboard().isUpPressed() && Globals::Instance()->getKeyboard().isDownPressed() )
	{
		m_yVelocity = m_zeroVelocity;
	}
	else
	{
		if ( Globals::Instance()->getKeyboard().isLeftPressed() )
		{
			m_xVelocity -= m_velocity;
			SetDirection(LEFT);
		}

		if ( Globals::Instance()->getKeyboard().isRightPressed() )
		{
			m_xVelocity += m_velocity;
			SetDirection(RIGHT);
		}
	}

	m_combat.SetAttackPressedPrevState(m_combat.IsAttackPressed());
	if (Globals::Instance()->getKeyboard().isSpaceBarPressed())
	{
		m_combat.SetAttackPressed(true);
	}
	else
	{
		m_combat.SetAttackPressed(false);
	}
}

void Player::Move()
{
	const Uint32 deltaTicks = Globals::Instance()->GetFrameRateRegulator().GetDelta();

	SDL_Rect futureRect;
	futureRect.w = Matter::m_rect.w;
	futureRect.h = Matter::m_rect.h;

    //Move the player left or right
	const int xAxisMovement = static_cast<Sint16>(Round(ForceProgress(m_xVelocity * static_cast<Sint32>(deltaTicks) / Matter::m_millisecondsPerSecond)));
	futureRect.x = Matter::m_rect.x + xAxisMovement;
	futureRect.y = Matter::m_rect.y;
	if (Globals::Instance()->getGame().GetMap().IsTilePassable(futureRect))
	{
		//Passable on X axis
		Matter::m_rect.x = futureRect.x;
	}
	else
	{
		//Player has moved onto impassable tile.  Back player off the impassable tile.
		while ((futureRect.x) % futureRect.w != 0)
		{
			assert(xAxisMovement  != 0);
			if (xAxisMovement > 0)
			{
				futureRect.x -= 1;
			}
			else
			{
				futureRect.x += 1;
			}
		}
		Matter::m_rect.x = futureRect.x;
	}

	//Move the dot up or down
	const int yAxisMovement = static_cast<Sint16>(Round(ForceProgress(m_yVelocity * static_cast<Sint32>(deltaTicks) / Matter::m_millisecondsPerSecond)));
    futureRect.y = Matter::m_rect.y + yAxisMovement;
	futureRect.x = Matter::m_rect.x;
	if (Globals::Instance()->getGame().GetMap().IsTilePassable(futureRect))
	{
		//Passable on Y axis
		Matter::m_rect.y = futureRect.y;
	}
	else
	{
		//Player has moved onto impassable tile.  Back player off the impassable tile.
		while ((futureRect.y) % futureRect.h != 0)
		{
			assert(yAxisMovement  != 0);
			if (yAxisMovement > 0)
			{
				futureRect.y -= 1;
			}
			else 
			{
				futureRect.y += 1;
			}
		}
		Matter::m_rect.y = futureRect.y;
	}
}

void Player::MoveCamera()
{
    //Center the camera over the dot
	Globals::Instance()->getGame().getCamera().x = ( Matter::m_rect.x + Matter::m_rect.w / 2 ) - Screen::Instance()->getScreenWidth() / 2;
    Globals::Instance()->getGame().getCamera().y = ( Matter::m_rect.y + Matter::m_rect.h / 2 ) - Screen::Instance()->getScreenHeight() / 2;

    //Keep the camera in bounds.
    if( Globals::Instance()->getGame().getCamera().x < 0 )
    {
        Globals::Instance()->getGame().getCamera().x = 0;    
    }
    if( Globals::Instance()->getGame().getCamera().y < 0 )
    {
        Globals::Instance()->getGame().getCamera().y = 0;    
    }
    if( Globals::Instance()->getGame().getCamera().x > m_mapWidth - Globals::Instance()->getGame().getCamera().w )
    {
        Globals::Instance()->getGame().getCamera().x = m_mapWidth - Globals::Instance()->getGame().getCamera().w;    
    }
    if( Globals::Instance()->getGame().getCamera().y > m_mapHeight - Globals::Instance()->getGame().getCamera().h )
    {
        Globals::Instance()->getGame().getCamera().y = m_mapHeight - Globals::Instance()->getGame().getCamera().h;    
    }    
}

void Player::Combat(std::vector<Enemy*>& enemies)
{
	std::vector<Enemy*>::const_iterator enemy_iter;
	for(enemy_iter = enemies.begin(); enemy_iter != enemies.end(); enemy_iter++)
	{
		if (IsCollision((*enemy_iter)->GetRect()))
		{
			if (m_combat.IsAttack())
			{
				//Enemy takes dmg
				(*enemy_iter)->GetCombat().TakeDamage(5);
			}
		}
	}
}

void Player::Animate()
{
	int clipIndexPrevState = m_clipIndex;

	if (m_combat.IsDead())
	{
		m_clipIndex = 2;
		switch(GetDirection())
		{
			case LEFT: case UPLEFT: case DOWNLEFT: m_clipIndex = 2; break;
			case RIGHT: case UPRIGHT: case DOWNRIGHT: m_clipIndex = 5; break;
			default: assert(false);
		}
	}
	else if (m_combat.IsAttackPressed())
	{
		m_clipIndex = 1;
		switch(GetDirection())
		{
			case LEFT: case UPLEFT: case DOWNLEFT: m_clipIndex = 1; break;
			case RIGHT: case UPRIGHT: case DOWNRIGHT: m_clipIndex = 4; break;
			default: assert(false);
		}
	}
	else
	{
		m_clipIndex = 0;
		switch(GetDirection())
		{
			case LEFT: case UPLEFT: case DOWNLEFT: m_clipIndex = 0; break;
			case RIGHT: case UPRIGHT: case DOWNRIGHT: m_clipIndex = 3; break;
			default: assert(false);
		}
	}

	if (m_clipIndex != clipIndexPrevState)
	{
		m_image = Image(m_imageFile, m_clips.at(m_clipIndex));
	}
}

bool Player::ReadXML()
{
	TiXmlDocument config( "Configs\\PlayerConfig.xml" );
	
	if ( !config.LoadFile() )
	{
		return false;
	}

	TiXmlNode* node = config.FirstChild("playerList")->FirstChild("player");
	if (!node)
	{
		return false;
	}

	while (m_playerName.compare(node->ToElement()->Attribute("instance")) != 0)
	{
		//Player name not a match.  Keep looking.
		node = node->NextSibling();
		if (!node)
		{
			//Searched all player names.  No match found.
			return false;
		}
	}

	node = node->FirstChild("image");
	if (!node)
	{
		return false;
	}
	std::stringstream iss (node->ToElement()->GetText());
	iss >> m_imageFile;
	iss.str(""); iss.clear();

	node = node->NextSibling("offset");
	if (!node)
	{
		return false;
	}
	iss << node->ToElement()->Attribute("x");
	iss >> Matter::m_rect.x;
	iss.str(""); iss.clear();
	iss << node->ToElement()->Attribute("y");
	iss >> Matter::m_rect.y;
	iss.str(""); iss.clear();

	node = node->NextSibling("rectIndex");
	if (!node)
	{
		return false;
	}
	iss << node->ToElement()->GetText();
	iss >> m_clipIndex;
	iss.str(""); iss.clear();

	int attributeNumber = 0;
	iss << "x" << attributeNumber;
	std::string attributeString = iss.str();
	iss.str(""); iss.clear();
	int attributeValue = 0;
	
	SDL_Rect tempRect;
	while (node->NextSiblingElement("rects")->QueryIntAttribute(attributeString.c_str(), &attributeValue) == TIXML_SUCCESS)
	{
		iss << attributeValue;
		iss >> tempRect.x;
		iss.str(""); iss.clear();

		iss << "y" << attributeNumber;
		attributeString = iss.str();
		iss.str(""); iss.clear();
		iss << node->NextSiblingElement("rects")->Attribute(attributeString.c_str());
		iss >> tempRect.y;
		iss.str(""); iss.clear();

		iss << "w" << attributeNumber;
		attributeString = iss.str();
		iss.str(""); iss.clear();
		iss << node->NextSiblingElement("rects")->Attribute(attributeString.c_str());
		iss >> tempRect.w;
		iss.str(""); iss.clear();

		iss << "h" << attributeNumber;
		attributeString = iss.str();
		iss.str(""); iss.clear();
		iss << node->NextSiblingElement("rects")->Attribute(attributeString.c_str());
		iss >> tempRect.h;
		iss.str(""); iss.clear();

		m_clips.push_back(tempRect);

		attributeNumber++;
		iss << "x" << attributeNumber;
		attributeString = iss.str();
		iss.str(""); iss.clear();
	}
	//If m_clips is empty the game has no players defined
	assert(!m_clips.empty());

	return true;
}
