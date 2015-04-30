#pragma once
#include "MenuGraphique.h"
#include "Phase.h"

class PhaseMenuGraphique : public Phase{

private:

	MenuGraphique* menuGraphique;


public:

	PhaseMenuGraphique() : Phase(){

		menuGraphique = new MenuGraphique();

	}

	~PhaseMenuGraphique() {

		delete menuGraphique;

	}

	void rafraichir(float frameTime){

	}

	void remplir(void) {

		menuGraphique->remplir();

	}

	void defPause(bool pause) {
		menuGraphique->defPause(pause);
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menuGraphique->actualiserEchelle(vecteurEchelle);
	}

};