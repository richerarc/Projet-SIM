#pragma once
#include "Menu.h"
#include "Texte2D.h"

class MenuGraphique : public Menu {

private:

	gfx::Texte2D* Resolution;
	Bouton* FlecheGauche;
	Bouton* FlecheDroite;
	Bouton* Appliquer;

public:

	MenuGraphique(void) : Menu() {

		

	}

	void remplir(void) {



	}
	void defPause(bool pause) {}

};