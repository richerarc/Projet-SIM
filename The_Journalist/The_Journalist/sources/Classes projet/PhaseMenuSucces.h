#pragma once
#include "MenuSucces.h"
#include "Phase.h"

class PhaseMenuSucces : public Phase{

private:

	MenuSucces* menuSucces;


public:

	PhaseMenuSucces() : Phase(){

		menuSucces = new MenuSucces();

	}

	~PhaseMenuSucces() {

		delete menuSucces;

	}

	void rafraichir(float frameTime) {
		menuSucces->survolSucces();
	}

	void remplir() {

		menuSucces->remplir();

	}

	void defPause(bool pause) {
		menuSucces->defPause(pause);
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menuSucces->actualiserEchelle(vecteurEchelle);
	}
};