	#if defined(__APPLE__) && defined(__MACH__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#elif defined _WIN32
//#pragma comment ( lib,"opengl32.lib")
//#pragma comment ( lib,"SDL2main.lib")
//#pragma comment ( lib,"SDL2.lib")
//#pragma comment ( lib,"SDL2_image.lib")
//#pragma comment ( lib,"SDL2_ttf.lib")
//#pragma comment ( lib,"SDL2_mixer.lib")
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//#pragma comment(linker, "/NODEFAULTLIB:msvcrt.lib")
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_opengl.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_opengl.h>
#endif

static int pol = 0;

#define VITESSE_PENIBLE 2.16e+06




#include "Jeu.h"
int main(int argc, char* argv[]){
	Jeu::demarrer();
	pol;
	return 0;
}
