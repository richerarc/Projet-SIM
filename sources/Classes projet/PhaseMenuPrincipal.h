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

		menuPrincipal->actualiser();
	}

	void remplir() {

	}
};