//#17
#include <SDL2/SDL.h>
#include "Salle.h"

bool ouvert = true;

//0<->1
//1->2
//1<->3
//3<->4
//4<->7


bool labyrinthe[8][8] = { { 0, 1, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 1, 0, 0, 0, 0 },
{ 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 0, 1, 0, 0, 0 },
{ 0, 0, 0, 1, 0, 0, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 1, 0, 0, 0 } };
Salle* salles[8];

void lectureTableau(SDL_Renderer* renderer){
	for (int i = 0; i < 8; i++){
		int nbrEntree = 0;
		for (int x = 0; x < 8; x++){
			if (labyrinthe[x][i] == true){
				nbrEntree++;
			}

		}
		salles[i] = new Salle(renderer, true, i, i, nbrEntree);

	}
}

void dessinerLabyrinthe(SDL_Renderer* renderer){
	for (int i = 0; i < 8;){
		int porte = 0;
		for (int y = 0; y < 8; y++){
			for (int x = 0; x < 8; x++){
				if (y == x){
					if (labyrinthe[i][i] == true){
						salles[i]->lierAvec(salles[i], true, 0, 1);

					}
				}
				else {
					if (x > i){
						if (labyrinthe[x][y] == true){
							salles[i]->lierAvec(salles[x], true, porte, porte);
							porte++;
							porte = porte % 4;
						}
					}
					else{
						if (labyrinthe[x][y] == true){
							salles[i]->lierAvec(salles[x], true, porte, porte);
							porte++;
							porte = porte % 4;
						}
					}
				}
			}
			i++;
		}
	}
}

int main(int argc, char** argv){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* m_pSDLWindow; // Création d'une fenêtre.
	SDL_Renderer* m_pSDLRenderer; // Création d'un render.
	SDL_CreateWindowAndRenderer(1280, 1024, NULL, &m_pSDLWindow, &m_pSDLRenderer); // Affichage de la fenêtre;
	SDL_Event* SDLEvent = new SDL_Event();
	SDL_SetRenderDrawColor(m_pSDLRenderer, 0, 0, 0, 255);
	lectureTableau(m_pSDLRenderer);
	while (ouvert){
		SDL_RenderPresent(m_pSDLRenderer);
		SDL_SetRenderDrawColor(m_pSDLRenderer, 255, 255, 255, 255);
		SDL_RenderClear(m_pSDLRenderer);

		while (SDL_PollEvent(SDLEvent)){
			switch (SDLEvent->type){
			case SDL_KEYDOWN:
				if (SDLEvent->key.keysym.sym == SDLK_ESCAPE){
					ouvert = false;
				}
			}
		}
		//Algorythme ici
		for (int i = 0; i < 8; i++){
			salles[i]->dessinerSalle();
		}
		dessinerLabyrinthe(m_pSDLRenderer);
		int a = 0;
	}
	SDL_Quit();
	return 0;
}