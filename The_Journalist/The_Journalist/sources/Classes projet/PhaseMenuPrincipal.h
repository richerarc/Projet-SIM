#pragma once 
#include "Phase.h"
#include "MenuPrincipal.h"

class PhaseMenuPrincipal : public Phase{

private:

	MenuPrincipal* menuPrincipal;

public:

	PhaseMenuPrincipal() : Phase(){

		menuPrincipal = new MenuPrincipal();
	}

	~PhaseMenuPrincipal() {

		delete menuPrincipal;
	}

	void rafraichir(float frameTime) {

	}

	void remplir() {

		menuPrincipal->remplir();

	}
	void defPause(bool pause) {
		menuPrincipal->defPause(pause);
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menuPrincipal->actualiserEchelle(vecteurEchelle);
	}
};