enum TypeMenu { MENUPRINCIPAL, MENUCONTROL, MENUGRAPHIQUE, MENUNOUVELLEPARTIE, MENUOPTIONS, MENUPAUSE, MENUSON, PHASEJEU };

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


public:

	Jeu(){}

	static void demarrer(){
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		TTF_Init();
		//Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048);
		//ControlleurAudio::obtInstance().initialiser(100);
		
		GestionnaireControle::obtInstance().lireControle("Controle.txt");

		fenetre = new gfx::Fenetre(gfx::ModeVideo(1280, 720), "CoffeeTrip", false);
		Rect<float>::defDimension(1280, 720);
		gfx::Gestionnaire3D::obtInstance().defFrustum(45, 800.0 / 600.0, 0.99, 1000);
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuPrincipal());		//0
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuControle());		//1
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuGraphique());		//2
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuNouvellePartie());	//3
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuOptions());			//4
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuPause());			//5
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuSon());				//6
		GestionnairePhases::obtInstance().defPhaseActive(MENUPRINCIPAL);
		GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
		GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);

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
			if (GestionnairePhases::obtInstance().obtPhaseActive() == nullptr)
				fenetre->fermer();
			else
				GestionnairePhases::obtInstance().rafraichir(frameTime);
		
			// Affichage ici
			gfx::Gestionnaire3D::obtInstance().defFrustum(45, 800.0 / 600.0, 0.99, 1000);
			gfx::Gestionnaire3D::obtInstance().afficherTout();
			gfx::Gestionnaire2D::obtInstance().afficherTout(*fenetre);
			

			fenetre->rafraichir();
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
