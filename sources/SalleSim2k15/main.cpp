//#17
#include <SDL2/SDL.h>
#include "Salle.h"

bool Open = true;

int main(int argc, char** argv){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* m_pSDLWindow; // Création d'une fenêtre.
	SDL_Renderer* m_pSDLRenderer; // Création d'un render.
	SDL_CreateWindowAndRenderer(1280, 1024, NULL, &m_pSDLWindow, &m_pSDLRenderer); // Affichage de la fenêtre;
	SDL_Event* SDLEvent = new SDL_Event();
	Salle* Piece1;
	Salle* Piece2;
	while (Open){
		SDL_RenderPresent(m_pSDLRenderer);
		SDL_SetRenderDrawColor(m_pSDLRenderer, 255, 255, 255, 255);
		SDL_RenderClear(m_pSDLRenderer);

		while (SDL_PollEvent(SDLEvent)){
			switch (SDLEvent->type){
			case SDL_KEYDOWN:
				if (SDLEvent->key.keysym.sym == SDLK_ESCAPE){
					Open = false;
				}
			}
		}
		//Algorythme ici
	}
	SDL_Quit();
	return 0;
}