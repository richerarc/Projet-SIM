#pragma once

#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)

#elif defined _WIN32

#endif

#include "Vecteur2.h"
#include <string>
namespace gfx{
	class Texture{
	private:
		SDL_Surface* surface;
		GLuint ID;
	public:

		Texture() {
			surface = nullptr;
			glGenTextures(1, &ID);
		}

		Texture(const char* path) {
			glGenTextures(1, &ID);
			charger(path);
		}

		~Texture() {
			if (surface != nullptr){
				if (surface->format != nullptr)
					SDL_FreeSurface(surface);
				surface = nullptr;
			}
		}

		bool charger(const char* path){
			surface = IMG_Load(path);
			if (surface != nullptr){
        glBindTexture(GL_TEXTURE_2D, ID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        
#if defined(__APPLE__) && defined(__MACH__)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
#elif defined _WIN32 || defined(__linux__)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
#endif
      }
			return (surface != nullptr);
		}

		GLuint obtID(){
			return ID;
		}

		Vecteur2d obtTaille() {
			return Vecteur2d(surface->w, surface->h);
		}

		SDL_Surface* obtSurface() {
			return surface;
		}
	};
}