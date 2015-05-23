#pragma once
#include "Phase.h"
#include "MenuFin.h"
class PhaseMenuFin : public Phase {
private:
	MenuFin* menuFin;

public:
	PhaseMenuFin(void) : Phase() {
		menuFin = new MenuFin();


	}

	~PhaseMenuFin() {

		delete menuFin;
	}

	void rafraichir(float frameTime) {

	}

	void remplir() {

		menuFin->remplir();

	}
	void defPause(bool pause) {
		menuFin->defPause(pause);
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menuFin->actualiserEchelle(vecteurEchelle);
	}

};