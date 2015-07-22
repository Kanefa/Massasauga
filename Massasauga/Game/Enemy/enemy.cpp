#include "enemy.h"
#include "../../Engine/globals.h"
#include "../../Engine/TinyXML/tinyxml.h"
#include "SDL.h"
#include <sstream>
#include <string>

Enemy::Enemy(const std::string EnemyName, int x, int y) : m_enemyName(EnemyName), m_clipIndex(0), m_combat(10, 0, 0, 1000)
{
	//Read properties from EnemyConfig.xml
	bool success = ReadXML();
	assert(success);

	//Load enemy sprite
	m_image = Image(m_imageFile, m_clips.at(m_clipIndex));

	//Set x,y coordinates
	Matter::m_rect.x = x;
	Matter::m_rect.y = y;

	//Set width and height
	Matter::m_rect.w = m_clips.at(m_clipIndex).w;
	Matter::m_rect.h = m_clips.at(m_clipIndex).h;
}

void Enemy::Show()
{
	m_image.ApplyImage(Matter::m_rect.x - Globals::Instance()->getGame().getCamera().x, Matter::m_rect.y - Globals::Instance()->getGame().getCamera().y, Matter::m_rect );
}

bool Enemy::ReadXML()
{
	TiXmlDocument config( "Configs\\EnemyConfig.xml" );
	
	if ( !config.LoadFile() )
	{
		return false;
	}

	TiXmlNode* node = config.FirstChild("enemyList")->FirstChild("enemy");
	if (!node)
	{
		return false;
	}

	while (m_enemyName.compare(node->ToElement()->Attribute("instance")) != 0)
	{
		//Enemy name not a match.  Keep looking.
		node = node->NextSibling();
		if (!node)
		{
			//Searched all enemy names.  No match found.
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
	//If m_clips is empty the game has no enemies defined
	assert(!m_clips.empty());

	return true;
}
