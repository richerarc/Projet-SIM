#pragma once
#include "PhaseMenuPause.h"
#include "Carte.h"
#include "GestionnaireControle.h"

class PhaseJeu : public Phase{

private:

	Joueur* joueur;
	gfx::Texte2D* texte;

	void appliquerPhysique(float frameTime) {
		if (joueur->obtVitesse().norme() != 0) {
			if (!Physique::obtInstance().collisionJoueurSalle(joueur)) {
				if (joueur->obtEtat() != STABLE)
					Physique::obtInstance().appliquerGravite(joueur->obtVitesse(), frameTime);
				joueur->defPosition(joueur->obtPosition() + joueur->obtVitesse() * frameTime);
			}
			else{
				if (joueur->obtEtat() != CHUTE)
					joueur->defEtat(CHUTE);
				else if (joueur->obtEtat() == CHUTE){
					if (Physique::obtInstance().collisionAuSol(joueur)){
						joueur->defEtat(STABLE);
						joueur->obtVitesse().y = 0.f;
					}
					else {
						joueur->obtVitesse().x = 0.f;
						joueur->obtVitesse().z = 0.f;
					}
				}

			}
		}
		Physique::obtInstance().appliquerPhysiqueSurListeObjet(frameTime);
	}

	

	void detectionObjet() {

		std::list<Objet*> liste = Carte::obtInstance().salleActive->obtListeObjet();
		bool objetDetecte = false;

		for (auto it : liste) {
			Porte* it_Porte = dynamic_cast<Porte*>(it);
			ObjetFixe* it_ObjFixe = dynamic_cast<ObjetFixe*>(it);
			if ((Physique::obtInstance().distanceEntreDeuxPoints(joueur->obtPosition(), it->obtPosition()) < 2) && (joueur->obtVectOrientationVue().angleEntreVecteurs(Physique::obtInstance().vecteurEntreDeuxPoints(joueur->obtPosition(), it->obtPosition())) <= 90.0)) {
				std::string str1 = "Press ";
				str1.append(GestionnaireControle::obtInstance().obtToucheControleEnChar((GestionnaireControle::obtInstance().obtenirControles()[UTILISER])));
				
				if (it_Porte != nullptr){
					str1.append(" to open door.");
				}
				else if (it_ObjFixe != nullptr)
					str1.append(" to pick up.");
				const char* chr1 = str1.c_str();
				texte->defTexte(chr1);
				gfx::Gestionnaire2D::obtInstance().ajouterObjet(texte);
				objetDetecte = true;
			}
		}

		if (!objetDetecte)
			gfx::Gestionnaire2D::obtInstance().retObjet(texte);
	}

public:

	PhaseJeu() : Phase(){
		joueur = new Joueur(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Joueur.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png")), Vecteur3d(-1, 0, 0));
		joueur->ajouterScene();
		texte = new gfx::Texte2D("123", "arial.ttf", 20, Vecteur2f(300, 200));

		Carte::obtInstance().creer(20);
		//Carte::obtInstance().salleActive = new Salle(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("SalleCarree4x4.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("SalleCarree4x4.png")), 2, 0);
	}

	void rafraichir(float frameTime) {

		if (!this->pause) {

			joueur->deplacement(frameTime);
			appliquerPhysique(frameTime);
			detectionObjet();
			//ControlleurAudio::obtInstance().jouerTout(joueur);
		}

		if (Clavier::toucheAppuyee(SDLK_ESCAPE)) {
			pause = true;
			GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuPause());
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_ShowCursor(SDL_ENABLE);
			gfx::Gestionnaire3D::obtInstance().obtCamera()->defPause(true);
		}
	}

	void remplir() {

	}
};