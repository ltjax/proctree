
set(TARGET_NAME happytree)
add_executable(${TARGET_NAME} WIN32
  diskio.cpp
  glstuff.cpp
  happytree.h
  imconfig.h
  imgui.cpp
  imgui.h
  imgui_impl.cpp
  main.cpp
  presets.cpp
  shader.cpp
  shader.h
  stb_image.c
  stb_image.h
  stb_rect_pack.h
  stb_textedit.h
  stb_truetype.h
  toolkit.cpp
  toolkit.h)


if (MSVC)
  target_compile_options(${TARGET_NAME} PUBLIC "/wd4996")
endif()

target_link_libraries(${TARGET_NAME}
  PUBLIC proctree
  PUBLIC CONAN_PKG::sdl2
  PUBLIC CONAN_PKG::glm
  PUBLIC CONAN_PKG::glew
  PUBLIC CONAN_PKG::nativefiledialog-extended
  PUBLIC OpenGL::GL)
