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
	static Joueur* joueur;

	static void appliquerPhysique() {

		if (joueur->obtVitesse().norme() != 0) {
			if (!Physique::obtInstance().collisionJoueurSalle(joueur)) {
				Physique::obtInstance().appliquerGravite(joueur->obtVitesse(), frameTime);
				joueur->defPosition(joueur->obtPosition() + joueur->obtVitesse() * frameTime);
			}
		}

		Physique::obtInstance().appliquerPhysiqueSurListeObjet(frameTime);

	}

public:

	Jeu(){}

	static void demarrer(){
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		TTF_Init();
		fenetre = new gfx::Fenetre(gfx::ModeVideo(800, 600), "CoffeeTrip",false);
		gfx::Gestionnaire3D::obtInstance().defFrustum(45,800.0/600.0,1,1000);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnable(GL_TEXTURE_2D);
		//fenetre->defModeVideo(gfx::ModeVideo::obtModes()[0]);
		joueur = new Joueur(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Joueur.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png")), 0, 87, Vecteur3d());
		frameTime = chrono.obtTempsEcoule().enSecondes();
		gfx::Modele3D* crate = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("boite.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("boite.png"));
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(crate);
		joueur->ajouterScene();
		
		crate->defPosition(0, 0, -5);
		crate->defOrigine(0, 0, 0);
		
		while (fenetre->estOuverte())
		{
			frameTime = chrono.obtTempsEcoule().enSecondes();
		
			while (fenetre->sonderEvenements(evenement))
			{
				GestionnaireEvenements::obtInstance().lancerEvenement(evenement);

				// Pour l'instant ce sera de cette facon qu'on quittera le jeu. plus tard se sera grace au menu pause j'imagine
				if (evenement.type == SDL_QUIT || evenement.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					fenetre->fermer();
			}
			fenetre->vider();
			glLoadIdentity();
			// Mouvement ici
			joueur->deplacement(frameTime);
			// Affichege ici
			gfx::Gestionnaire3D::obtInstance().afficherTout();

			fenetre->rafraichir();
		}
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		delete joueur;
		delete fenetre;
		TTF_Quit();
		SDL_Quit();
	}
	
};

float Jeu::frameTime = 0;
gfx::Fenetre* Jeu::fenetre = nullptr;
Chrono Jeu::chrono;
Joueur* Jeu::joueur = nullptr;
SDL_Event Jeu::evenement;