#pragma once
#include "MenuSon.h"
#include "Phase.h"

class PhaseMenuSon : public Phase{

private:

	MenuSon* menuSon;


public:

	PhaseMenuSon() : Phase(){

		menuSon = new MenuSon();

	}

	~PhaseMenuSon() {

		delete menuSon;

	}

	void rafraichir(float frameTime) {

	}

	void remplir() {

		menuSon->remplir();

	}
	void defPause(bool pause) {
		menuSon->defPause(pause);
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menuSon->actualiserEchelle(vecteurEchelle);
	}

};