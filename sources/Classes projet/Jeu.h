#pragma once
#include "Lecteur.h"
#include "Fenetre.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire3D.h"
#include "Gestionnaire2D.h"
#include "GestionnaireEvenements.h"
#include "Objet.h"
/*
#include les classes plus bases plus tard
*/
#include "ObjetFixe.h"
#include "Porte.h"
#include "ObjetPhysique.h"
#include "Vent.h"
#include "Aimant.h"
#include "Porte.h"
#include "Carte.h"
#include "Joueur.h"
#include "Salle.h"
#include "Physique.h"


class Jeu{

private:
	static gfx::Fenetre *fenetre;
	static SDL_Event evenement;
public:

	Jeu(){}

	static void demarrer(){
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		TTF_Init();
		fenetre = new gfx::Fenetre(gfx::ModeVideo(800, 600), "CoffeeTrip",true);
		fenetre->defModeVideo(gfx::ModeVideo::obtModes()[0]);
		while (fenetre->estOuverte())
		{
			fenetre->vider();
			while (fenetre->sonderEvenements(evenement))
			{
				GestionnaireEvenements::obtInstance().lancerEvenement(evenement);

				// Pour l'instant ce sera de cette facon qu'on quittera le jeu. plus tard se sera grace au menu pause j'imagine
				if (evenement.type == SDL_QUIT || evenement.key.keysym.sym == SDLK_ESCAPE)
					fenetre->fermer();
			}

			// Mouvement ici


			// Affichege ici

			fenetre->rafraichir();
		}	
		delete fenetre;
		TTF_Quit();
		SDL_Quit();
	}
	
};

gfx::Fenetre* Jeu::fenetre = nullptr;
SDL_Event Jeu::evenement;