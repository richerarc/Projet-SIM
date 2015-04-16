#pragma once
#include "MenuOptions.h"
#include "Phase.h"

class PhaseMenuOptions : public Phase{

private:

	MenuOptions* menuOptions;


public:

	PhaseMenuOptions() : Phase(){

		menuOptions = new MenuOptions();

	}

	~PhaseMenuOptions() {

		delete menuPause;

	}

	void rafraichir(){

		menuOptions->actualiser();

	}


};