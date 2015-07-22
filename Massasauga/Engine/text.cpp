#include "text.h"
#include "screen.h"
#include "SDL_image.h"
#include <cassert>

Text::Text(std::string textMessage, std::string fontName, int fontSize, int red, int green, int blue) : m_font(NULL), m_surface(NULL)
{
	m_textColor.r = red;
	m_textColor.g = green;
	m_textColor.b = blue;
	m_textColor.unused = 0;

	m_font = TTF_OpenFont(fontName.c_str(), fontSize);
	if ( !m_font )
	{
		assert(false);
		exit(1);
	}

	CreateTexture(textMessage);
}

Text::~Text()
{
	TTF_CloseFont(m_font);
	glDeleteTextures(1, &m_texture);
	SDL_FreeSurface(m_surface);
}

void Text::Apply(int x, int y)
{
	GLBlit(x, y);
}

void Text::Update(std::string textMessage, int red, int green, int blue)
{
	m_textColor.r = red;
	m_textColor.g = green;
	m_textColor.b = blue;
	m_textColor.unused = 0;

	if ( !m_font )
	{
		assert(false);
		exit(1);
	}

	UpdateTexture(textMessage);
}

void Text::CreateTexture(std::string textMessage)
{
   CreateSDLSurface(textMessage);

   GLuint texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_surface->w, m_surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_surface->pixels);
   m_texture = texture;
}

void Text::UpdateTexture(std::string textMessage)
{
   CreateSDLSurface(textMessage);

   glBindTexture(GL_TEXTURE_2D, m_texture);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_surface->w, m_surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_surface->pixels);
}

void Text::CreateSDLSurface(std::string textMessage)
{
	if (m_surface != NULL)
	{
		SDL_FreeSurface(m_surface);
		m_surface = NULL;
	}
	m_surface = TTF_RenderText_Blended(m_font, textMessage.c_str(), m_textColor);
	if (!m_surface)
	{
		assert(false);
		exit(1);
	}
}

void Text::GLBlit(int x, int y) 
{
	int z = 0;

	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex3d(x, y, z);
		glTexCoord2d(1, 0); glVertex3d(x + m_surface->w, y, z);
		glTexCoord2d(1, 1); glVertex3d(x + m_surface->w, y + m_surface->h, z);
		glTexCoord2d(0, 1); glVertex3d(x, y + m_surface->h, z);
	glEnd();
}
