#include "image.h"
#include "screen.h"
#include "SDL_image.h"
#include <string>
#include <cassert>

Image::Image()
{
}

Image::Image( std::string filename, SDL_Rect clip )
{
   CreateTexture(filename, clip);
}

Image::Image(const Image &image)
{
	m_texture.texture_number = image.m_texture.texture_number;
	m_texture.texcoord[0] = image.m_texture.texcoord[0];
	m_texture.texcoord[1] = image.m_texture.texcoord[1];
	m_texture.texcoord[2] = image.m_texture.texcoord[2];
	m_texture.texcoord[3] = image.m_texture.texcoord[3];
}

Image & Image::operator=(const Image &image)
{
	//This gracefully handles self assignment
	if (this == &image) 
	{	
		return *this;
	}

	m_texture.texture_number = image.m_texture.texture_number;
	m_texture.texcoord[0] = image.m_texture.texcoord[0];
	m_texture.texcoord[1] = image.m_texture.texcoord[1];
	m_texture.texcoord[2] = image.m_texture.texcoord[2];
	m_texture.texcoord[3] = image.m_texture.texcoord[3];

	return *this;
}

void Image::ApplyImage( int x, int y, SDL_Rect rect)
{
	GLBlit(x, y, rect);
}

void Image::CreateTexture(std::string filename, SDL_Rect clip) 
{
   //Creates texture from image file
   SDL_Surface *unoptimizedImage = IMG_Load(filename.c_str());
   if (!unoptimizedImage)
   {
      assert(false);
      exit(1);
   }

   SDL_Surface *optimizedImage = SDL_DisplayFormat( unoptimizedImage );
   SDL_FreeSurface( unoptimizedImage );
   if ( !optimizedImage )
   {
      assert(false);
      exit(1);
   }

   Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xff, 0xff, 0xff );
   if ( SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey) == -1 )
   {
	   assert(false);
	   exit(1);
   }

   const int w = PowerOfTwo(clip.w);
   const int h = PowerOfTwo(clip.h);
   m_texture.texcoord[0] = 0.0f;
   m_texture.texcoord[1] = 0.0f;
   m_texture.texcoord[2] = (GLfloat)clip.w / w;
   m_texture.texcoord[3] = (GLfloat)clip.h / h;

   //blit from bitmap to temporary surface
   Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
   const int bpp = Screen::Instance()->getScreenBPP();
   SDL_Surface *temporaryImage = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, bpp, rmask, gmask, bmask, amask);
   SDL_BlitSurface(optimizedImage, &clip, temporaryImage, NULL);

   // create GL texture
   GLuint texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temporaryImage->pixels);

   m_texture.texture_number = texture;

   SDL_FreeSurface(temporaryImage);
   SDL_FreeSurface(optimizedImage);
}

int Image::PowerOfTwo(int input) 
{
   int value = 1;

   while (value < input)
   {
      value <<= 1;
   }

   return value;
}

void Image::GLBlit(int x, int y, SDL_Rect rect) 
{
   GLfloat texMinX, texMinY;
   GLfloat texMaxX, texMaxY;

   //Easier to understand the coordinates for the texture
   texMinX = m_texture.texcoord[0];
   texMinY = m_texture.texcoord[1];
   texMaxX = m_texture.texcoord[2];
   texMaxY = m_texture.texcoord[3];

   glBindTexture(GL_TEXTURE_2D, m_texture.texture_number);

   //Draw polygon
   glBegin(GL_TRIANGLE_STRIP);
   glTexCoord2f(texMinX, texMinY); 
   glVertex2i(x, y);
   glTexCoord2f(texMaxX, texMinY); 
   glVertex2i(x + rect.w, y);
   glTexCoord2f(texMinX, texMaxY); 
   glVertex2i(x, y + rect.h);
   glTexCoord2f(texMaxX, texMaxY); 
   glVertex2i(x + rect.w, y + rect.h);
   glEnd();
}