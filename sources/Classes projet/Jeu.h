#pragma once
#include "Lecteur.h"
#include "Fenetre.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire3D.h"
#include "Gestionnaire2D.h"
#include "GestionnaireEvenements.h"
#include "Objet.h"
#include "ObjetFixe.h"
#include "ObjetInventaire.h"
#include "ObjetPhysique.h"
#include "Vent.h"
#include "Aimant.h"
#include "Porte.h"
#include "Salle.h"
#include "Piece.h"
#include "Connecteur.h"
#include "Carte.h"


class Jeu{

private:
	static gfx::Fenetre *fenetre;
	static SDL_Event evenement;
	static gfx::Gestionnaire3D gestionnaire3D;
	static gfx::Gestionnaire2D gestionnaire2D;
	static gfx::GestionnaireRessources gestionnaireRessources;
public:

	Jeu(){}

	static void demarrer(){
		fenetre = new gfx::Fenetre(gfx::ModeVideo(800, 600), "CoffeeTrip", false);
		while (fenetre->estOuverte())
		{
			fenetre->vider();
			while (fenetre->sonderEvenements(evenement))
			{
				//Pour l'instant ce sera de cette facon qu'on quittera le jeu. plus tard se sera grace au menu pause j'imagine
				if (evenement.type == SDL_QUIT || evenement.key.keysym.sym == SDL_SCANCODE_ESCAPE)
					fenetre->fermer();
			}

			//Mouvement ici


			//Affichege ici

			fenetre->rafraichir();
		}	
		delete fenetre;
	}
};

gfx::Fenetre* Jeu::fenetre = nullptr;
SDL_Event Jeu::evenement;