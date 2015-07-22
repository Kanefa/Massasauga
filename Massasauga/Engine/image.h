#ifndef IMAGE_H
#define IMAGE_H

#include "SDL.h"
#include "SDL_opengl.h"
#include <string>

class Image
{
public:
	Image();
	Image(std::string filename, SDL_Rect clip);
	Image(const Image &image);
	Image & operator=(const Image &image);
	void ApplyImage(int x, int y, SDL_Rect rect);

private:
	void CreateTexture(std::string filename, SDL_Rect clip);
	static int PowerOfTwo(int input);
	void GLBlit(int x, int y, SDL_Rect rect);

	struct Texture
	{
		GLuint texture_number;
		GLfloat texcoord[4];
	} m_texture;
};
#endif