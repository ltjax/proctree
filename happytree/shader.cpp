/*  HappyTree
*  version 1.0, January 10th, 2015
*
*  Copyright (C) 2015 Jari Komppa
*
*  This software is provided 'as-is', without any express or implied
*  warranty.  In no event will the authors be held liable for any damages
*  arising from the use of this software.
*
*  Permission is granted to anyone to use this software for any purpose,
*  including commercial applications, and to alter it and redistribute it
*  freely, subject to the following restrictions:
*
*  1. The origin of this software must not be misrepresented; you must not
*     claim that you wrote the original software. If you use this software
*     in a product, an acknowledgment in the product documentation would be
*     appreciated but is not required.
*  2. Altered source versions must be plainly marked as such, and must not be
*     misrepresented as being the original software.
*  3. This notice may not be removed or altered from any source distribution.
*
* Jari Komppa http://iki.fi/sol/
*
*************************************
*
*/
#include "happytree.h"

Shader::Shader()
{
	mVSSrc = 0;
	mVSLen = 0;
	mFSSrc = 0;
	mFSLen = 0;
}

Shader::~Shader()
{
	delete[] mFSSrc;
	delete[] mVSSrc;
}

void Shader::init(char const* aFilename_vs, char const* aFilename_fs)
{
	delete[] mVSSrc;
	delete[] mFSSrc;
	mVSSrc = loadfile(aFilename_vs, mVSLen);
	mFSSrc = loadfile(aFilename_fs, mFSLen);
}

void Shader::build()
{
	char *vs_src_p[1] = { mVSSrc };
	char *fs_src_p[1] = { mFSSrc };
	int status = GL_FALSE;

	int vs_obj = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_obj, 1, (const char**)vs_src_p, &mVSLen);
	glCompileShader(vs_obj);
  glGetShaderiv(vs_obj, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		char temp[2048];
		glGetShaderInfoLog(mShaderHandle, 2048, &status, temp);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Shader compile failure", temp, gWindow);
	}

  status = GL_FALSE;
	int fs_obj = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_obj, 1, (const char**)fs_src_p, &mFSLen);
	glCompileShader(fs_obj);
	glGetShaderiv(fs_obj, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		char temp[2048];
		glGetShaderInfoLog(mShaderHandle, 2048, &status, temp);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Shader compile failure", temp, gWindow);
	}

	status = GL_FALSE;
	mShaderHandle = glCreateProgram();
	glAttachShader(mShaderHandle, vs_obj);
	glAttachShader(mShaderHandle, fs_obj);
	glLinkProgram(mShaderHandle);
	glGetProgramiv(mShaderHandle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		char temp[2048];
		glGetProgramInfoLog(mShaderHandle, 2048, &status, temp);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Shader link failure", temp, gWindow);
	}
}

void Shader::use()
{
	glUseProgram(mShaderHandle);
}

int Shader::uniformLocation(char const* aName)
{
	return glGetUniformLocation(mShaderHandle, aName);
}

