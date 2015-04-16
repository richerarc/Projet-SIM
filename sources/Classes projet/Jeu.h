#pragma once
#include "Singleton.h"
#include "Fenetre.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire3D.h"
#include "Gestionnaire2D.h"
#include "GestionnaireEvenements.h"
#include "GestionnairePhases.h"
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
#include "GestionnaireControle.h"
#include "PhaseJeu.h"
#include "MenuPrincipal.h"
#include "PhaseMenuPrincipal.h"
#include "PhaseMenuNouvellePartie.h"
#include "PhaseMenuPause.h"



class Jeu{

public:

	static gfx::Fenetre *fenetre;
	static SDL_Event evenement;
	static float frameTime;
	static Chrono chrono;

	Jeu(){}

	static void demarrer(){
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		TTF_Init();
		//Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048);
		//ControlleurAudio::obtInstance().initialiser(100);
		
		
		fenetre = new gfx::Fenetre(gfx::ModeVideo(800, 600), "CoffeeTrip", false);
		gfx::Gestionnaire3D::obtInstance().defFrustum(45, 800.0 / 600.0, 0.99, 1000);
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuPrincipal());
		//fenetre->defModeVideo(gfx::ModeVideo::obtModes()[0]);

		Rect<float>::defDimension(600);

		frameTime = chrono.repartir().enSecondes();
		while (fenetre->estOuverte())
		{
			frameTime = chrono.repartir().enSecondes();
			while (fenetre->sonderEvenements(evenement))
			{
				GestionnaireEvenements::obtInstance().lancerEvenement(evenement);
			}

			fenetre->vider();
			glLoadIdentity();
			// Mouvement ici
			GestionnairePhases::obtInstance().rafraichir(frameTime);
		
			// Affichege ici
			gfx::Gestionnaire3D::obtInstance().afficherTout();
			gfx::Gestionnaire2D::obtInstance().afficherTout(*fenetre);
			

			fenetre->rafraichir();
			if (GestionnairePhases::obtInstance().obtPhase(0) == nullptr)
				fenetre->fermer();
		}
		
		delete fenetre;
		//ControlleurAudio::obtInstance().fermer();
		//Mix_CloseAudio();
		TTF_Quit();
		SDL_Quit();
	}

};

gfx::Fenetre* Jeu::fenetre = nullptr;
SDL_Event Jeu::evenement;
float Jeu::frameTime = 0;
Chrono Jeu::chrono;