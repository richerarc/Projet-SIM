#pragma once
#include "Vecteur2.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
namespace gfx{
	class Texture{
	private:
		SDL_Surface* surface;
		GLuint ID;
	public:

		Texture(){
			surface = nullptr;
		}

		~Texture(){
			if (surface != nullptr){
				SDL_FreeSurface(surface);
				surface = nullptr;
			}
		}

		bool charger(const char* path){
			surface = IMG_Load(path);
			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->w, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			return (surface != NULL);
		}

		GLuint obtID(){
			return ID;
		}

		Vecteur2ui obtTaille(){
			return Vecteur2ui(surface->w, surface->h);
		}

		SDL_Surface* obtSurface(){
			return surface;
		}
	};
}