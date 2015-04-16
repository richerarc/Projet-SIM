#pragma once
#include "Menu.h"
#include "Texte2D.h"

class MenuOptions : public Menu {

private:

	gfx::Texte2D* Graphique;
	gfx::Texte2D* Son;
	gfx::Texte2D* Controle;

public:

	MenuOptions(void) : Menu() {
		
		

	}


};