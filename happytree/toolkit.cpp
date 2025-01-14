#include <math.h>
#include "toolkit.h"

struct texpair
{
    const char *mFilename;
    GLuint mHandle;
    int mClamp;
	int mWidth, mHeight;
	unsigned char *mData;
};

SDL_Window* gWindow = nullptr;
int gScreenWidth = DESIRED_WINDOW_WIDTH;
int gScreenHeight = DESIRED_WINDOW_HEIGHT;
UIState gUIState = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
texpair * gTextureStore = NULL;
int gTextureStoreSize = 0;


void initvideo(char const* title, int argc)
{
    int flags = 0;

#ifdef _DEBUG
    int fsflag = 0;
#else
#ifdef FULLSCREEN_BY_DEFAULT
    int fsflag = 1;
#else
    int fsflag = 0;
#endif
#endif

    if (argc > 1) fsflag = !fsflag;

    if (fsflag) 
    {
        flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    else
    {
        if (argc == 0)
        {
            // window was resized
        }
        flags = SDL_WINDOW_OPENGL;
#ifdef RESIZABLE_WINDOW
        flags |= SDL_WINDOW_RESIZABLE;
#endif
    }

    // request OpenGL 3.3 context.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenWidth, gScreenHeight, flags);
    if (gWindow == 0)
    {
        fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError());
        SDL_Quit();
        exit(0);
    }

    auto context = SDL_GL_CreateContext(gWindow);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        SDL_Quit();
        exit(0);
    }
   
    glViewport( 0, 0, gScreenWidth, gScreenHeight );

    reload_textures();    
}


static unsigned char * do_loadtexture(const char * aFilename, int &aWidth, int &aHeight, int clamp = 1, unsigned char *aData = 0)
{
	// Load texture using stb
	unsigned char *data = NULL;
	int w, h;
	
	data = aData;
	w = aWidth;
	h = aHeight;
	
    // Tell OpenGL to read the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)data);
	glGenerateMipmap(GL_TEXTURE_2D);

    //// and cleanup.
	//stbi_image_free(data);

    if (clamp)
    {
        // Set up texture parameters
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }
    else
    {
        // Set up texture parameters
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
	return data;
}

char * mystrdup(const char *aString)
{
	auto len = strlen(aString);
	char * d = new char[len+1];
	memcpy(d, aString, len);
	d[len] = 0;
	return d;
}

GLuint load_texture(char const* aFilename, int clamp)
{
    // First check if we have loaded this texture already
	int i, j, w, h, n;
	for (i = 0; i < gTextureStoreSize; i++)
    {
        if (stricmp(gTextureStore[i].mFilename, aFilename) == 0)
            return gTextureStore[i].mHandle;
    }

    // Create OpenGL texture handle and bind it to use

    GLuint texname;
    glGenTextures(1,&texname);
    glBindTexture(GL_TEXTURE_2D,texname);

	gTextureStoreSize++;

	texpair * t = (texpair *)realloc(gTextureStore, sizeof(texpair) * gTextureStoreSize);
	if (t != NULL)
	{
		gTextureStore = t;
		gTextureStore[gTextureStoreSize - 1].mFilename = mystrdup(aFilename);
		gTextureStore[gTextureStoreSize - 1].mHandle = texname;
		gTextureStore[gTextureStoreSize - 1].mClamp = clamp;
	}
	

	gTextureStore[gTextureStoreSize - 1].mData = stbi_load(aFilename, &w, &h, &n, 4);

	unsigned int * src = (unsigned int*)gTextureStore[gTextureStoreSize - 1].mData;

	// mark all pixels with alpha = 0 to black
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			if ((src[i * w + j] & 0xff000000) == 0)
				src[i * w + j] = 0;
		}
	}
	
	gTextureStore[gTextureStoreSize - 1].mWidth = w;
	gTextureStore[gTextureStoreSize - 1].mHeight = h;

	return texname;
}

int gLazyLoadIndex = 0;
void lazyTextureLoad()
{
	int j;
	for (j = 0; j < 5; j++)
	{
		if (gLazyLoadIndex >= gTextureStoreSize)
			return;
		int i = gLazyLoadIndex;
		glBindTexture(GL_TEXTURE_2D, gTextureStore[i].mHandle);
		do_loadtexture(gTextureStore[i].mFilename,
			gTextureStore[i].mWidth,
			gTextureStore[i].mHeight,
			gTextureStore[i].mClamp,
			gTextureStore[i].mData);
		gLazyLoadIndex++;
	}
}

void reload_textures()
{
	gLazyLoadIndex = 0;
	int i;
	GLuint dummy;
	for (i = 0; i < gTextureStoreSize; i++)
		glGenTextures(1, &dummy);
}

