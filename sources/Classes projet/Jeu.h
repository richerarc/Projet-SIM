#pragma once
#include "Singleton.h"
#include "Fenetre.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire3D.h"
#include "Gestionnaire2D.h"
#include "GestionnaireEvenements.h"
#include "Objet.h"
#include "Sons.h"
#include "ControlleurAudio.h"
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
				if (joueur->obtEtat() != STABLE)
					Physique::obtInstance().appliquerGravite(joueur->obtVitesse(), frameTime);
				joueur->defPosition(joueur->obtPosition() + joueur->obtVitesse() * frameTime);
			}
			else{
				if (joueur->obtEtat() == SAUT)
					joueur->defEtat(CHUTE);
				else if (joueur->obtEtat() == CHUTE){
					joueur->defEtat(STABLE);
					joueur->obtVitesse().y = 0.f;
				}

			}
		}
		Physique::obtInstance().appliquerPhysiqueSurListeObjet(frameTime);
	}

public:

	Jeu(){}

	static void demarrer(){
		srand(time(NULL));
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		TTF_Init();
		Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048);
		ControlleurAudio::obtInstance().initialiser(100);


		fenetre = new gfx::Fenetre(gfx::ModeVideo(800, 600), "CoffeeTrip", false);
		gfx::Gestionnaire3D::obtInstance().defFrustum(30, 800.0 / 600.0, 1, 1000);

		joueur = new Joueur(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Joueur.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png")), Vecteur3d(-1, 50, 0));
		frameTime = chrono.obtTempsEcoule().enSecondes();
		joueur->ajouterScene();

		//Carte::obtInstance().creer(20);
		Carte::obtInstance().salleActive = new Salle(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("SalleCarree4x4.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("SalleCarree4x4.png")), 2, 0);
		
		while (fenetre->estOuverte())
		{
			frameTime = chrono.repartir().enSecondes();

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
			appliquerPhysique();

			// Affichege ici
			gfx::Gestionnaire3D::obtInstance().afficherTout();
			ControlleurAudio::obtInstance().jouerTout(joueur);

			fenetre->rafraichir();
		}

		delete joueur;
		delete fenetre;
		ControlleurAudio::obtInstance().fermer();
		Mix_CloseAudio();
		TTF_Quit();
		SDL_Quit();
	}

};

float Jeu::frameTime = 0;
gfx::Fenetre* Jeu::fenetre = nullptr;
Chrono Jeu::chrono;
Joueur* Jeu::joueur = nullptr;
SDL_Event Jeu::evenement;