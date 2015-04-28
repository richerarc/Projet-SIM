#pragma once
#include "MenuControle.h"
#include "Phase.h"

class PhaseMenuControle : public Phase{

private:

	MenuControle* menuControle;


public:

	PhaseMenuControle() : Phase(){

		menuControle = new MenuControle();

	}

	~PhaseMenuControle() {

		delete menuControle;

	}

	void rafraichir(float frameTime){

	}

	void remplir(void) {

		menuControle->remplir();

	}

	void defPause(bool pause) {

		menuControle->defPause(pause);
		this->pause = pause;

	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menuControle->actualiserEchelle(vecteurEchelle);
	}

};