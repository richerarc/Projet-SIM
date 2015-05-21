enum TypeMenu { MENUPRINCIPAL, MENUCONTROL, MENUGRAPHIQUE, MENUNOUVELLEPARTIE, MENUOPTIONS, MENUPAUSE, MENUSON, MENUINVENTAIRE, PHASEJEU };

#pragma once
#include <sstream>
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
gfx::Fenetre* fenetre;
#include "Curseur.h"
Curseur* curseur;
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
#include "Physique.h"
#include "Joueur.h"
#include "Salle.h"
#include "PhaseJeu.h"
#include "MenuPrincipal.h"
#include "PhaseMenuPrincipal.h"
#include "PhaseMenuNouvellePartie.h"
#include "PhaseMenuPause.h"

class Jeu{

public:

	static SDL_Event evenement;
	static float frameTime;
	static Chrono chrono;
	static Chrono actualisationFPS;
	static gfx::Texte2D* fps;

public:

	Jeu(){

	}

	static void demarrer(){
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER);
		TTF_Init();
		Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048);
		ControlleurAudio::obtInstance().initialiser(100);
		
		
		fenetre = new gfx::Fenetre(gfx::ModeVideo(1280, 720), "CoffeeTrip", false);

		fps = new gfx::Texte2D(new std::string("0"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 15), Vecteur2f(0, 700));

		GestionnaireControle::obtInstance().lireControle("Ressources/Info/Controle.txt");

		Rect<float>::defDimension(1280, 720);
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

		//fenetre->defModeVideo(gfx::ModeVideo::obtModes()[0]);
		curseur = new Curseur(Vecteur2f(500, 500));
		curseur->remplir();
		frameTime = chrono.repartir().enSecondes();
		GestionnaireSucces::obtInstance().initialiser();
		GestionnaireSucces::obtInstance().reinitialiserListe();
		while (fenetre->estOuverte())
		{
			if (actualisationFPS.obtTempsEcoule().enSecondes() > 0.2f){
				std::stringstream ss;
				ss << "The Journalist v0.134" << " @ " << 1 / frameTime << " fps";
				actualisationFPS.repartir();
				fps->defTexte(new std::string(ss.str()));
			}
			PhaseJeu* phase = dynamic_cast<PhaseJeu*>(GestionnairePhases::obtInstance().obtDerniere());
			if (phase != nullptr) {
				char chr[100];
					fenetre->defTitre(std::string(SDL_itoa(Carte::obtInstance().obtInstance().salleActive->obtID(), chr, 10)));
			}

			if (Carte::obtInstance().finChargement) {
				double hAngle;
				Vecteur3d positionJoueur = Carte::obtInstance().debut(hAngle);
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().obtPhaseActive()->defPause(true);
				GestionnairePhases::obtInstance().ajouterPhase(new PhaseJeu(positionJoueur, hAngle));
				GestionnairePhases::obtInstance().defPhaseActive(PHASEJEU);
				Carte::obtInstance().finChargement = false;
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
			//Succès expirés ici
			GestionnaireSucces::obtInstance().verifierTempsAffichage();
			// Mouvement ici
			if (GestionnairePhases::obtInstance().obtPhaseActive() == nullptr)
				fenetre->fermer();
			else
				GestionnairePhases::obtInstance().rafraichir(frameTime);
		
			// Affichage ici
			gfx::Gestionnaire3D::obtInstance().defFrustum(2.5 , fenetre->obtRatio(), .1, 1000);
			gfx::Gestionnaire3D::obtInstance().afficherTout();
			gfx::Gestionnaire2D::obtInstance().afficherTout(*fenetre);
			fps->afficher(*fenetre);

			fenetre->rafraichir();
		}
		GestionnaireSucces::obtInstance().tuerGestionnaireSucces();
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
Chrono Jeu::actualisationFPS;
gfx::Texte2D* Jeu::fps;