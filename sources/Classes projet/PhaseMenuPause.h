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

		menuPause->actualiser();

	}

	void remplir() {

	}
};