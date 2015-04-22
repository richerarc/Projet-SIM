#pragma once
#include "MenuSon.h"
#include "Phase.h"

class PhaseMenuSon : public Phase{

private:

	MenuSon* menuSon;


public:

	PhaseMenuSon() : Phase(){

		menuSon = new MenuSon();

	}

	~PhaseMenuSon() {

		delete menuSon;

	}

	void rafraichir(float frameTime) {

	}

	void remplir() {

		menuSon->remplir();

	}

};