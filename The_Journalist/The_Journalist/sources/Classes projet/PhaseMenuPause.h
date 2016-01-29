#pragma once
#include "MenuPause.h"

class PhaseMenuPause : public Phase{

private:

	MenuPause* menuPause;


public:

	PhaseMenuPause() : Phase(){

		menuPause = new MenuPause();

	}

	~PhaseMenuPause() {

		delete menuPause;

	}

	void rafraichir(float frameTime){

	}

	void remplir() {

		menuPause->remplir();

	}

	void defPause(bool pause) {
		menuPause->defPause(pause);
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menuPause->actualiserEchelle(vecteurEchelle);
	}
};