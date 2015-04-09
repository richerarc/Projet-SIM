#pragma once
#include "Menu.h"

class MenuGraphique : public Menu {

private:

	Etiquette* Resolution;
	Bouton* FlecheGauche;
	Bouton* FlecheDroite;
	Bouton* Appliquer;

public:

	MenuGraphique(void) : Menu() {

		this->Actif = false;
		this->SpriteFond = new gfx::Sprite2D();
		this->Titre = new Etiquette();
		this->Retour = new Bouton();

		this->Resolution = new Etiquette();
		this->FlecheGauche = new Bouton();
		this->FlecheDroite = new Bouton();
		this->Appliquer = new Bouton();

	}

	bool obtActif(void) {
		return Actif;
	}

	void defActif(bool Actif) {
		this->Actif = Actif;
	}


};