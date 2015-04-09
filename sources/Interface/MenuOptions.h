#pragma once
#include "Menu.h"

class MenuOptions : public Menu {

private:

	Bouton* Graphique;
	Bouton* Son;
	Bouton* Controle;

public:

	MenuOptions(void) : Menu() {
		
		this->Actif = false;
		this->SpriteFond = new gfx::Sprite2D();
		this->Titre = new Etiquette();
		this->Retour = new Bouton();

		this->Graphique = new Bouton();
		this->Son = new Bouton();
		this->Controle = new Bouton();



	}

	bool obtActif(void) {
		return Actif;
	}

	void defActif(bool Actif) {
		this->Actif = Actif;
	}


};