#pragma once
#include "Singleton.h"
#include "Fenetre.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire3D.h"
#include "Gestionnaire2D.h"
#include "GestionnaireEvenements.h"
#include "Objet.h"
#include "ControlleurAudio.h"
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
	static Joueur* joueur;
	static Chrono chrono;
	static float frameTime;

//	static void appliquerPhysique() {
//
////		if (joueur->obtVitesse().norme() != 0) {
////			if (!Physique::obtInstance().collisionJoueurSalle(joueur)) {
////				Physique::obtInstance().appliquerGravite(joueur->obtVitesse(), frameTime);
////				joueur->defPosition(joueur->obtPosition() + joueur->obtVitesse() * frameTime);
////			}
////		}
////
////	Physique::obtInstance().appliquerPhysiqueSurListeObjet(frameTime);
//
//	}
public:

	Jeu(){}

	static void demarrer(){
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		TTF_Init();
		fenetre = new gfx::Fenetre(gfx::ModeVideo(800, 600), "The Journalist", false);
			//joueur = new Joueur(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Joueur.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png")), 0, 87, Vecteur3d());
		frameTime = chrono.obtTempsEcoule().enSecondes();

		// Pour le moment : En attendant que la génération génère la map elle-même.
			//Carte::obtInstance().salleActive = new Salle(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("pieceL.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("PieceL.png")), 0, 0);

//		Lecteur lecteur;
//		lecteur.allouerChaines(10);
//		
//		lecteur.ajouterSon("fond.ogg", "fond");
//		lecteur.ajouterSon("coeur.ogg", "coeur");
//		lecteur.ajouterSon("grillage.ogg", "grille");
//		lecteur.ajouterSon("papier1.ogg", "papier");
//		lecteur.creerChaine(1, "fond");
//		lecteur.creerChaine(2, "coeur");
//		lecteur.creerChaine(3, "grille");
//			//lecteur.creerChaine(4, "papier");
//		
//		
//		lecteur.jouerSon("fond", -1, 10000, -1);
//		lecteur.jouerSon("coeur", -1, 15000, -1);
//		lecteur.jouerSon("grille", 1, 20000, -1);

		ControlleurAudio::obtInstance().allouerChaines(50);
		ControlleurAudio::obtInstance().initialiser();
		
		while (fenetre->estOuverte())
		{
			frameTime = chrono.obtTempsEcoule().enSecondes();
			fenetre->vider();
			while (fenetre->sonderEvenements(evenement))
			{
				GestionnaireEvenements::obtInstance().lancerEvenement(evenement);

				// Pour l'instant ce sera de cette facon qu'on quittera le jeu. plus tard se sera grace au menu pause j'imagine
				if (evenement.type == SDL_QUIT || evenement.key.keysym.sym == SDLK_ESCAPE)
					fenetre->fermer();
			}
			
			// Mouvement ici
				//joueur->deplacement(frameTime);
				//appliquerPhysique();

			// Affichege ici
			gfx::Gestionnaire3D::obtInstance().afficherTout();

			fenetre->rafraichir();
		}
		delete joueur;
		delete fenetre;
		TTF_Quit();
		SDL_Quit();
	}
	
};

float Jeu::frameTime = 0;
gfx::Fenetre* Jeu::fenetre = nullptr;
Joueur* Jeu::joueur = nullptr;
Chrono Jeu::chrono;
SDL_Event Jeu::evenement;