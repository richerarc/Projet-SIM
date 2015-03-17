//#17
#include <SDL2/SDL.h>
#include "Salle.h"

bool ouvert = true;

//0<->1
//1->2
//1<->3
//3<->4
//4<->7

int nbrSalles = 15;
int nbrSallesParRangee = nbrSalles / 10 + 1;

bool labyrinthe[15][15] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
Salle* salles[8];

void lectureTableau(SDL_Renderer* renderer){
	int X = 0;
	int Y = 0;
	for (int i = 0; i < nbrSalles;i++){
		int nbrEntree = 0;
		for (int x = 0; x < nbrSalles; x++){
			if (labyrinthe[x][i] == true){
				nbrEntree++;
			}

		}
		/*
		
		salles[i] = new Salle(renderer, true, X, y, nbrEntree);
		X = (X + 10/nbrSallesParRangee);
		if (X >= 9){
			X = 0;
			y++;
		}
		*/
		salles[i] = new Salle(renderer, true, X, Y, nbrEntree);
		X = X + 2;
		if (X >= 10){
			Y++;
			X = 0;
		}
	}
}

void dessinerLabyrinthe(SDL_Renderer* renderer){
	for (int i = 0; i < nbrSalles;){
		int porte = 0;
		for (int y = 0; y < nbrSalles; y++){
			for (int x = 0; x < nbrSalles; x++){
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
		for (int i = 0; i < nbrSalles; i++){
			salles[i]->dessinerSalle();
		}
		dessinerLabyrinthe(m_pSDLRenderer);
		int a = 0;
	}
	SDL_Quit();
	return 0;
}