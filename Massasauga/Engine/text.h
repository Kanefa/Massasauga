#ifndef TEXT_H
#define TEXT_H

#include "SDL_ttf.h"
#include "SDL_opengl.h"
#include <string>

class Text
{
public:
	Text(std::string textMessage = "DEFAULT TEXT", std::string fontName = "fonts\\arial.ttf", int fontSize = 28, int red = 255, int green = 255, int blue = 255);
	~Text();
	void Apply(int x, int y);
	void Update(std::string textMessage = "DEFAULT UPDATE TEXT", int red = 255, int green = 255, int blue = 255);
	
private:
	Text(const Text &); // disallow copy constructor
	Text & operator=(const Text &); // disallow assignment operator
	void CreateTexture(std::string textMessage);
	void UpdateTexture(std::string textMessage);
	void CreateSDLSurface(std::string textMessage);
	void GLBlit(int x, int y);

	TTF_Font* m_font;
	SDL_Color m_textColor;
	SDL_Surface* m_surface;
	GLuint m_texture;
};
#endif