#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2 / SDL_opengl.h>
#include <math.h>
#include <list>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <tuple>
#include <set>
#include <functional>
#include <fstream>
#include "Vecteur2.h"
#include "Vecteur3.h"
#include "Texture.h"
#include "Souris.h"
#include "Clavier.h"
#include "Fenetre.h"
#include "Gestionnaire2D.h"
#include "Objet2D.h"
#include "Texte2D.h"
#include "Sprite2D.h"


int main(int argc, char* argv[]){
	gfx::Gestionnaire2D* gestionnaire = new gfx::Gestionnaire2D();
	gfx::Fenetre fenetre = gfx::Fenetre(gfx::ModeVideo(750, 750), "test", false);

	while (fenetre.estOuverte()){
		SDL_Event event;
		while (fenetre.sonderEvenements(event)){
			if (event.type == SDL_QUIT)
				fenetre.fermer();
		}
		fenetre.vider();



		fenetre.rafraichir();

	}
	return 0;
}