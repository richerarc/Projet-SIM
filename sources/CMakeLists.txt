cmake_minimum_required(VERSION 3.1)

project(PROJET)

if(APPLE)
set(SDL2_INCLUDE_DIR /Library/Frameworks/SDL2.framework/Headers/SDL.h)
set(SDL2_IMGAME_DIR /Library/Frameworks/SDL2_image.framework/Headers/SDL_image.h)
set(GL_INCLUDE_DIR /System/Library/Frameworks/OpenGL.framework/Headers/OpenGL.h)
set(SDL2_LIBRARY /usr/local/lib/libSDL2.dylib)
set(GL_LIBRARY /usr/local/lib/libGL.dylib)
else(APPLE)
set(SDL2_INCLUDE_DIR /usr/local/include/SDL2/SDL.h)
set(GL_INCLUDE_DIR /usr/include/GL/gl.h)
set(SDL2_LIBRARY /usr/local/lib/libSDL2.so)
set(GL_LIBRARY /usr/lib/x86_64-linux-gnu/libGL.so)
endif(APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GL_INCLUDE_DIR})

set(SOURCE_FILES main.cpp)
add_executable(PROJET ${SOURCE_FILES})
if(APPLE)

else(APPLE)
target_link_libraries(PROJET ${SDL2_LIBRARY})
target_link_libraries(PROJET ${GL_LIBRARY})
endif(APPLE)