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
	//Piece1 = new Salle(m_pSDLRenderer, true, 0, 0,3);
	//Piece2 = new Salle(m_pSDLRenderer, false, 5, 5,2);
	SDL_Rect Rectangle;
	Rectangle.x = 0;
	Rectangle.y = 0;
	Rectangle.w = 90;
	Rectangle.h = 90;
	SDL_SetRenderDrawColor(m_pSDLRenderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(m_pSDLRenderer, &Rectangle);
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
		/* Exemple fonctionnel
		Piece1->dessinerSalle();
		Piece1->lierAvec(Piece2, false, 1, 0);
		Piece1->lierAvec(Piece2, true, 1, 1);
		Piece1->lierAvec(Piece2, false, 1, 2);
		Piece1->lierAvec(Piece2, true, 1, 3);
		
		Piece2->dessinerSalle();
		
		*/
	}
	SDL_Quit();
	return 0;
}