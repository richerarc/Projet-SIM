#pragma once
#include "Fenetre.h"
#include "Gestionnaire3D.h"
#include "Gestionnaire2D.h"
#include "GestionnaireRessources.h"
#include "GestionnaireEvenements.h"


class Jeu{

private:
	static gfx::Fenetre fenetre;
	static SDL_Event evenement;

public:


	static void demarrer(){
		fenetre = gfx::Fenetre(gfx::ModeVideo(800, 600), "CoffeeTrip", false);
		while (fenetre.estOuverte())
		{
			fenetre.vider();
			while (fenetre.sonderEvenements(evenement))
			{
				//Pour l'instant ce sera de cette facon qu'on quittera le jeu. plus tard se sera grace au menu pause j'imagine
				if (evenement.type == SDL_QUIT || evenement.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					fenetre.fermer();		
			}
			fenetre.rafraichir();

		}
		
	}
};

gfx::Fenetre Jeu::fenetre = gfx::Fenetre(gfx::ModeVideo(0,0),NULL,false);
SDL_Event Jeu::evenement;