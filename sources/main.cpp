// Point
#if defined(__APPLE__) && defined(__MACH__) && defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif defined _WIN32
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
#endif

#include "Jeu.h"
// Les bananes en pyjamas sont vraiment magnifiques
int main(int argc, char* argv[]){
	Jeu::demarrer();
	return 0;
}
