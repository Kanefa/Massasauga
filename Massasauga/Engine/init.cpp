#include "init.h"
#include "screen.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"
#include <cassert>

Init::Init()
{
	//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        exit(1);
		assert(false);
    }

	if ( TTF_Init() == -1 )
	{
      assert(false);
      exit(1);
	}

	_putenv("SDL_VIDEO_CENTERED=center");

    //Set up the screen
	Screen::Instance()->setScreen( SDL_SetVideoMode( Screen::Instance()->getScreenWidth(), Screen::Instance()->getScreenHeight(), Screen::Instance()->getScreenBPP(), SDL_OPENGL ) );
    
    //If there was an error in setting up the screen
    if( Screen::Instance()->getScreen() == NULL )
    {
        exit(1);
		assert(false);
    }

	atexit(SDL_Quit);

	if ( !InitOpenGL() )
	{
		exit(1);
		assert(false);
	}

    //Set the window caption
    SDL_WM_SetCaption( "OpenGL Test", NULL );
}

bool Init::InitOpenGL()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glAlphaFunc(GL_GREATER, 0);	//full opacity or none.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.0, 0.0, 1.0f); //set to white

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Screen::Instance()->getScreenWidth(), Screen::Instance()->getScreenHeight(), 0.0, 0.0, 1.0); //set coordinate system

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	bool result = true;
    if( glGetError() != GL_NO_ERROR )
    {
        result = false;    
    }

	return true;
}

#if defined (_DEBUG)
void Init::DebugOpenGL()
{
	const GLubyte* result = glGetString( GL_RENDERER );
	result = glGetString( GL_VENDOR );
	result = glGetString( GL_VERSION );
	result = glGetString( GL_EXTENSIONS );
}
#endif
