#pragma once
#include "Menu.h"
#include "Texte2D.h"

class MenuGraphique : public Menu {

private:

	gfx::Texte2D* Resolution;
	gfx::Texte2D* FlecheGauche;
	gfx::Texte2D* FlecheDroite;
	gfx::Texte2D* Appliquer;

public:

	MenuGraphique(void) : Menu() {

		

	}

	void actualiser() {



	}


};