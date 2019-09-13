# ProcTree

This is a liberally licensed procedural tree generator in c++, along with an editor HappyTree.

[![Quick walkthrough of 20150123 version](http://img.youtube.com/vi/XLBvkVMxdS0/0.jpg) (youtube video)](http://www.youtube.com/watch?v=XLBvkVMxdS0) 

The procedural generation itself is a port from https://github.com/supereggbert/proctree.js/
see http://snappytree.com for an online demonstration of the original proctree.js (with webgl). The c++ port is several orders of magnitude faster than the original, and also fixes the UV mapping.

# Fork Info

This fork of proctree and happytree works nicely on Windows, Linux and Mac OS. It replaces a few dependencies:
  - SDL2 instead of SDL
  - nativefiledialog-extended instead of Win32 FileDialogs
  - Boost.Filesystem instead of Win32 Directory iteration
  - glew instead of GLee

## Building
The new fork uses conan for dependency management and CMake as a build system generator. E.g. to build on linux
```
# First add the required remotes (only do this once)
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add ltjax https://api.bintray.com/conan/ltjax/conan 

# Create a build folder and grab dependencies and generate build files
mkdir build && cd build
conan install .. -s build_type=Release -s compiler.libcxx=libstd++11 --build missing
cmake .. -DCMAKE_BUILD_TYPE=Release

# Now build
make
```
**Warning:** Be sure to run happytree in the `happytree/` folder so it can find its `data/` folder. It will fail silently if you do not.

## Binaries

Download win32 binaries at:
http://iki.fi/sol/zip/happytree_20150123.zip

Additional (not mandatory) 400 megs of trunk / twig textures
http://iki.fi/sol/zip/happytree_20150118_tex.zip

If you opt to download the additional textures, just unzip both zips in the same place. HappyTree will work without the additional textures (it'll actually be faster), so if you're just trying it out, I recommend NOT downloading the additional stuff.

All of the textures are CC0 / public domain material (primarily, if not completely, by nobiax.deviantart.com). The additional textures do let you make more varieties of trees though; the base package only comes with one trunk and twig texture.

The happytree editor requires OpenGL 3.3, but seriously, who doesn't have that?

Usage should be pretty intuitive, you can rotate the camera by dragging and zoom in and out with the mouse wheel.

## Motivation

I wanted a tree generator I can use to generate trees at runtime in C.

## License

The generator itself is licensed under 3-clause BSD license (personally I'd have opted
for something even more liberal, but that's what the original proctree.js used). See
the source file for the actual license.

The editor's sources and support libraries are under variety of bsd and zlib liceses.
See legal_notes.txt in the happytree directory for details.

## Dependencies

The generator itself has no dependencies, and was designed to be easily plugged into whatever.

The editor (HappyTree) has a bunch of dependencies:

  - proctree (naturally)  
  - GLee opengl extension library (included)
  - stb_image image loading library (included)
  - My modified opengl framework (included)
  - Ocornut's ImGui library (included)
  - SDL 1.2 cross-platform library
  - glm gl math library
  
## Notes

The ported proctree.cpp does not generate exactly the same output as the original proctree.js.
This may be partially due to the different math accuracy used, but it's possible that I
managed to slip a bug or two into the algorithm. (Feel free to debug..)

## Anything else?

Feel free to contact me, http://iki.fi/sol/
  
