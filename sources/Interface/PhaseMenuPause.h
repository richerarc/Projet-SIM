#pragma once
#include "MenuPause.h"

class PhaseMenuPause {

private:

	MenuPause* menuPause;


public:

	PhaseMenuPause() {

		menuPause = new MenuPause();

	}

	~PhaseMenuPause() {

		delete menuPause;

	}

	void rafraichir(){

		menuPause->actualiser();

	}


};