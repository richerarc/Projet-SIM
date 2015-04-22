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

		delete menuOptions;

	}

	void rafraichir(float frameTime) {

	}

	void remplir() {

		menuOptions->remplir();

	}

};