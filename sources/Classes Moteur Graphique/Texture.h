#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include "Vecteur2.h"
class Texture{
public:
	SDL_Surface* surface;
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
		surface = SDL_LoadBMP(path);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
		return (surface != NULL);
	}
	Vecteur2ui obtTaille(){
		return Vecteur2ui(surface->w, surface->h);
	}
	SDL_Surface* obtSurface(){
		return surface;
	}
};