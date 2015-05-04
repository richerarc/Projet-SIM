enum TypeMenu { MENUPRINCIPAL, MENUCONTROL, MENUGRAPHIQUE, MENUNOUVELLEPARTIE, MENUOPTIONS, MENUPAUSE, MENUSON, MENUCHARGEMENT, PHASEJEU };

#pragma once
#include <thread>
#include "Singleton.h"
#include "Fenetre.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire3D.h"
#include "Gestionnaire2D.h"
#include "GestionnaireEvenements.h"
#include "GestionnairePhases.h"
#include "Curseur.h"
#include "Objet.h"
#include "Sons.h"
#include "ControlleurAudio.h"
gfx::Fenetre *fenetre;
Curseur* curseur;
std::thread thread_Creation;
/*
#include les classes plus bases plus tard
*/
#include "Rect.h"
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
#include "PhaseMenuChargement.h"

class Jeu{

public:

	static SDL_Event evenement;
	static float frameTime;
	static Chrono chrono;

public:

	Jeu(){

	}

	static void demarrer(){
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER);
		TTF_Init();
		Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048);
		ControlleurAudio::obtInstance().initialiser(100);
		
		GestionnaireControle::obtInstance().lireControle("Controle.txt");

		fenetre = new gfx::Fenetre(gfx::ModeVideo(1280, 720), "CoffeeTrip", false);
		Rect<float>::defDimension(1280, 720);
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuPrincipal());		//0
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuControle());		//1
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuGraphique());		//2
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuNouvellePartie());	//3
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuOptions());			//4
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuPause());			//5
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuSon());				//6
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuChargement());
		GestionnairePhases::obtInstance().defPhaseActive(MENUPRINCIPAL);
		GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
		GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);

		//fenetre->defModeVideo(gfx::ModeVideo::obtModes()[0]);
		curseur = new Curseur(Vecteur2f(500, 500));
		curseur->remplir();
		PhaseMenuChargement* chargement;
		frameTime = chrono.repartir().enSecondes();
		while (fenetre->estOuverte())
		{
			PhaseJeu* phase = dynamic_cast<PhaseJeu*>(GestionnairePhases::obtInstance().obtDerniere());
			if (phase != nullptr) {
				char chr[100];
				fenetre->defTitre(std::string(SDL_itoa(Carte::obtInstance().obtInstance().salleActive->obtID(), chr, 10)));
			}
			chargement = dynamic_cast<PhaseMenuChargement*>(GestionnairePhases::obtInstance().obtPhaseActive());
			if (chargement != nullptr) {
				chargement->actualiserChargement(Carte::obtInstance().chargement);
			}

			if (Carte::obtInstance().finChargement) {
				Carte::obtInstance().debut();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().obtPhaseActive()->defPause(true);
				GestionnairePhases::obtInstance().ajouterPhase(new PhaseJeu());
				GestionnairePhases::obtInstance().defPhaseActive(PHASEJEU);
				Carte::obtInstance().finChargement = false;
				thread_Creation.detach();
				thread_Creation.~thread();
				Carte::obtInstance().salleActive->remplir();
			}


			frameTime = chrono.repartir().enSecondes();
			curseur->rafraichir();
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
			gfx::Gestionnaire3D::obtInstance().defFrustum(45, fenetre->obtRatio(), 1, 1000);
			gfx::Gestionnaire3D::obtInstance().afficherTout();
			gfx::Gestionnaire2D::obtInstance().afficherTout(*fenetre);
			

			fenetre->rafraichir();
		}
		
		delete fenetre;
		ControlleurAudio::obtInstance().fermer();
		Mix_CloseAudio();
		TTF_Quit();
		SDL_Quit();
	}
};

SDL_Event Jeu::evenement;
float Jeu::frameTime = 0;
Chrono Jeu::chrono;