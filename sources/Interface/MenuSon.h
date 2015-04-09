#pragma once
#include "Menu.h"

class MenuSon : public Menu {

public:

	Glisseur* Volume;


	MenuSon(void) : Menu() {

		this->Actif = false;
		this->SpriteFond = new gfx::Sprite2D();
		this->Titre = new Etiquette();
		this->Retour = new Bouton();

		this->Volume = new Glisseur();

	}

	bool obtActif(void) {
		return Actif;
	}

	void defActif(bool Actif) {
		this->Actif = Actif;
	}


};