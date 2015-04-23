#pragma once
#include "Menu.h"
#include "Texte2D.h"
#include "Glisseur.h"

class MenuSon : public Menu {

private:

	gfx::Texte2D* volumeJeu;
	Glisseur* volume;


public:

	MenuSon(void) : Menu() {
		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));
		volumeJeu = new gfx::Texte2D("Game sound", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial50", 50), Vecteur2f(100, 500));
		this->retour = new Bouton(std::bind(&MenuSon::enClicRetour, this, std::placeholders::_1),
			std::bind(&MenuSon::survol, this, std::placeholders::_1),
			std::bind(&MenuSon::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 30),
			"Back", 50);

		volume = new Glisseur(Vecteur2f(100, 400), Vecteur2f(1,1), 50);
		defPause(true);
	}
	~MenuSon(void) {
		gfx::Gestionnaire2D::obtInstance().retObjets({ this->spriteFond , volumeJeu });
		delete this->spriteFond , volumeJeu;
	}
	void survol(Bouton* envoi){
		envoi->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* envoi){
		envoi->defCouleur({ 0, 0, 0, 255 });
	}
	void remplir(void) {
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, volumeJeu });
		volume->remplir();
		retour->remplir();
	}
	void enClicRetour(Bouton* envoi){
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().defPhaseActive(4);
				GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
	}

	void defPause(bool pause) {



	}

};