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

	void defPause(bool pause) {
		menuOptions->defPause(pause);
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menuOptions->actualiserEchelle(vecteurEchelle);
	}

};