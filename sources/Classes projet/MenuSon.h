#pragma once
#include "Menu.h"
#include "Texte2D.h"
#include "Glisseur.h"

class MenuSon : public Menu {

private:

	gfx::Texte2D* volumeJeu;
	Glisseur* volume;


public:

	MenuSon(void) : Menu() {

		

	}

	void remplir(void) {

		

	}

	void defPause(bool pause) {}
};