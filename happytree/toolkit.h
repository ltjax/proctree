#ifndef TOOLKIT_H
#define TOOLKIT_H

////
//// Configuration
//// 

// For windowed mode
#define DESIRED_WINDOW_WIDTH (1280)
// For windowed mode
#define DESIRED_WINDOW_HEIGHT (800)

//#define FULLSCREEN_BY_DEFAULT

#define RESIZABLE_WINDOW

////
//// /Configuration
//// 

#ifdef _MSC_VER
#define WINDOWS_VERSION
#endif

#ifdef __APPLE__
#define OSX_VERSION
#endif

#if !defined(WINDOWS_VERSION) && !defined(OSX_VERSION)
#define LINUX_VERSION
#endif


#include <SDL.h>
#include "stb_image.h"
#include <GL/glew.h>

#ifdef WINDOWS_VERSION
#define stricmp _stricmp
#define strdup _strdup
#endif


#ifdef OSX_VERSION
#define stricmp(a,b) strcasecmp((a),(b))
#endif


#ifdef LINUX_VERSION
#define stricmp(a,b) strcasecmp((a),(b))
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _MSC_VER
#pragma warning(disable:4244) 
#pragma warning(disable:4305) 
#endif


// If you're going to render widgets to the same
// UI from different source files, you can avoid
// ID collisions by defining IMGUI_SRC_ID before
// this define block:
#ifdef IMGUI_SRC_ID
#define GEN_ID ((IMGUI_SRC_ID) + (__LINE__))
#else
#define GEN_ID (__LINE__)
#endif


struct UIState
{
	int mousex;
	int mousey;
	int not_imgui_mousedown;
	int mousedown;

    int mousedownx;
    int mousedowny;
    int scroll;

	int hotitem;
	int activeitem;

    int lasthotitem;
    int lasthottick;

	int kbditem;
	int keyentered;
	int keymod;
	int keychar;
	
	int lastwidget;
};

extern UIState gUIState;

enum keystates
{
    KEY_UP    = 1,
    KEY_DOWN  = 2,
    KEY_LEFT  = 4,
    KEY_RIGHT = 8,
    KEY_FIRE  = 16
};

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

extern int gScreenWidth, gScreenHeight;
extern SDL_Window* gWindow;

void initvideo(char const* title, int argc);

GLuint load_texture(char const* aFilename, int clamp = 1);
void reload_textures();


#endif
