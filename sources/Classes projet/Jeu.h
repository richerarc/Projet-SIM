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
#include "Pendule.h"
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
	static Chrono chrono;
	static float frameTime;


public:

	Jeu(){}

	static void demarrer(){
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		TTF_Init();
		fenetre = new gfx::Fenetre(gfx::ModeVideo(800, 600), "CoffeeTrip",false);
		gfx::Gestionnaire3D::obtInstance().defFrustum(45,800.0/600.0,1,1000);
		//fenetre->defModeVideo(gfx::ModeVideo::obtModes()[0]);
		frameTime = chrono.obtTempsEcoule().enSecondes();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		gfx::Modele3D* crate = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("pieceL.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("PieceL.png"));
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(crate);
		crate->defPosition(0, 0, -5);
		crate->defOrigine(0, 0, 0);
		while (fenetre->estOuverte())
		{
			frameTime = chrono.obtTempsEcoule().enSecondes();
		
			while (fenetre->sonderEvenements(evenement))
			{
				GestionnaireEvenements::obtInstance().lancerEvenement(evenement);

				// Pour l'instant ce sera de cette facon qu'on quittera le jeu. plus tard se sera grace au menu pause j'imagine
				if (evenement.type == SDL_QUIT || evenement.key.keysym.sym == SDLK_ESCAPE)
					fenetre->fermer();
			}
			fenetre->vider();
			glLoadIdentity();
			// Mouvement ici

			// Affichege ici
			gfx::Gestionnaire3D::obtInstance().afficherTout();

			fenetre->rafraichir();
		}
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		delete fenetre;
		TTF_Quit();
		SDL_Quit();
	}
	
};

float Jeu::frameTime = 0;
gfx::Fenetre* Jeu::fenetre = nullptr;
Chrono Jeu::chrono;
SDL_Event Jeu::evenement;