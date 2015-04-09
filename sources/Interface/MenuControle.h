#pragma once
#include "Menu.h"

class MenuControle : public Menu {

private:

	Etiquette* Avancer;
	Etiquette* Reculer;
	Etiquette* Droite;
	Etiquette* Gauche;
	Etiquette* Sauter;
	Etiquette* Accroupir;
	Etiquette* Courir;
	Etiquette* Tirer;
	Etiquette* Utiliser;
	Etiquette* Inventaire;

	Bouton* CtrlAvancer;
	Bouton* CtrlReculer;
	Bouton* CtrlDroite;
	Bouton* CtrlGauche;
	Bouton* CtrlSauter;
	Bouton* CtrlAccroupir;
	Bouton* CtrlCourir;
	Bouton* CtrlTirer;
	Bouton* CtrlUtiliser;
	Bouton* CtrlInventaire;

public:

	MenuControle(void) : Menu() {

		this->Actif = false;
		this->SpriteFond = new gfx::Sprite2D();
		this->Titre = new Etiquette();
		this->Retour = new Bouton();

		
		this->Avancer = new Etiquette();
		this->Reculer = new Etiquette();
		this->Droite = new Etiquette();
		this->Gauche = new Etiquette();
		this->Sauter = new Etiquette();
		this->Accroupir = new Etiquette();
		this->Courir = new Etiquette();
		this->Tirer = new Etiquette();
		this->Utiliser = new Etiquette();
		this->Inventaire = new Etiquette();

		this->CtrlAvancer = new Bouton();
		this->CtrlReculer = new Bouton();
		this->CtrlDroite = new Bouton();
		this->CtrlGauche = new Bouton();
		this->CtrlSauter = new Bouton();
		this->CtrlAccroupir = new Bouton();
		this->CtrlCourir = new Bouton();
		this->CtrlTirer = new Bouton();
		this->CtrlUtiliser = new Bouton();
		this->CtrlInventaire = new Bouton();



	}

	bool obtActif(void) {
		return Actif;
	}

	void defActif(bool Actif) {
		this->Actif = Actif;
	}


};