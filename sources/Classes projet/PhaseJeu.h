#pragma once
#include "PhaseMenuPause.h"

class PhaseJeu : public Phase{

private:

	Joueur* joueur;
	gfx::Texte2D* texte;
	Objet* objetVise;
	bool toucheRelachee;

	void appliquerPhysique(float frameTime) {
		if (joueur->obtVitesse().norme() != 0) {
			if (!Physique::obtInstance().collisionJoueurSalle(Carte::obtInstance().salleActive, joueur)) {
				if (joueur->obtEtat() != STABLE)
					Physique::obtInstance().appliquerGravite(joueur->obtVitesse(), frameTime);
				joueur->defPosition(joueur->obtPosition() + joueur->obtVitesse() * frameTime);
			}
			else{
				if (joueur->obtEtat() != CHUTE)
					joueur->defEtat(CHUTE);
				else if (joueur->obtEtat() == CHUTE){
					if (Physique::obtInstance().collisionAuSol(Carte::obtInstance().salleActive, joueur)){
						joueur->defEtat(STABLE);
						joueur->obtVitesse().y = 0.f;
					}
					joueur->obtVitesse().x = 0.f;
					joueur->obtVitesse().z = 0.f;
				}
			}
		}
		Physique::obtInstance().appliquerPhysiqueSurListeObjet(Carte::obtInstance().salleActive, frameTime);
	}

	bool detectionObjet() {

		std::list<Objet*> liste = Carte::obtInstance().salleActive->obtListeObjet();
		bool objetDetecte = false;

		for (auto it : liste) {
			if (Physique::obtInstance().distanceEntreDeuxPoints(joueur->obtPosition(), it->obtPosition()) < 2) {
				texte->defTexte(new std::string("Press E to open the door"));
				gfx::Gestionnaire2D::obtInstance().ajouterObjet(texte);
				objetDetecte = true;
				objetVise = it;
				return objetDetecte;
			}
		}

		if (!objetDetecte)
			gfx::Gestionnaire2D::obtInstance().retObjet(texte);
		return objetDetecte;
	}

public:

	PhaseJeu() : Phase(){
		joueur = new Joueur(Vecteur3d(-1, 0, 0));
		joueur->ajouterScene();
		texte = new gfx::Texte2D(new std::string("123"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 20), Vecteur2f(300, 200));
		toucheRelachee = false;
		
		//Carte::obtInstance().salleActive = new Salle(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("SalleCarree4x4.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("SalleCarree4x4.png")), 2, 0);
		
		Carte::obtInstance().creer(20);
	}

	void rafraichir(float frameTime) {

		if (!this->pause) {

		
			joueur->deplacement(frameTime);
			appliquerPhysique(frameTime);
			detectionObjet();
			ControlleurAudio::obtInstance().jouer(COEUR, joueur);
			ControlleurAudio::obtInstance().jouer(PAS, joueur);
			detectionObjet();
			ControlleurAudio::obtInstance().jouerTout(joueur);
		}

		if (Clavier::toucheAppuyee(SDLK_ESCAPE)) {
			defPause(true);
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_ShowCursor(SDL_ENABLE);
			gfx::Gestionnaire3D::obtInstance().obtCamera()->bloquer();
			GestionnairePhases::obtInstance().defPhaseActive(MENUPAUSE);
			GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);
			GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
		}


		if (detectionObjet()){
			if (Clavier::toucheAppuyee(SDLK_e) && toucheRelachee){// Touche relachée bientôt...
				if (objetVise->obtSiPorte()){
					Carte::obtInstance().destination(std::make_tuple(Carte::obtInstance().salleActive->obtID(), objetVise->obtID(), false), *joueur);
				}
				else{
					objetVise->appliquerAction(Interagir);
				}
				toucheRelachee = false;
			}
			if (Clavier::toucheAppuyee(SDLK_e))
				toucheRelachee = true;
		}
	}

	void remplir() {

	}

	void defPause(bool pause) {
		this->pause = pause;
	}
};

