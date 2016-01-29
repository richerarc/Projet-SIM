#pragma once
#include "MenuNouvellePartie.h"
#include "Phase.h"

class PhaseMenuNouvellePartie : public Phase {

private:

	MenuNouvellePartie* menuNouvellePartie;


public:

	PhaseMenuNouvellePartie() : Phase() {

		menuNouvellePartie = new MenuNouvellePartie();

	}

	~PhaseMenuNouvellePartie() {

		delete menuNouvellePartie;

	}

	void rafraichir(float frameTime){

	}

	void remplir() {

		menuNouvellePartie->remplir();

	}

	void defPause(bool pause) {
		menuNouvellePartie->defPause(pause);
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menuNouvellePartie->actualiserEchelle(vecteurEchelle);
	}
};