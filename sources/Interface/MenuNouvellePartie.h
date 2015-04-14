//#pragma once
//#include "Menu.h"
//
//class MenuNouvellePartie : public Menu {
//
//private:
//
//	Etiquette ChoisirDiff;
//	Bouton Facile;
//	Bouton Normal;
//	Bouton Difficile;
//
//
//public:
//
//	MenuNouvellePartie(void) : Menu() {
//
//		this->Actif = false;
//		this->SpriteFond = new gfx::Sprite2D();
//		this->Titre = new Etiquette();
//		this->Retour = new Bouton();
//
//		this->ChoisirDiff = new Etiquette();
//		this->Facile = new Bouton();
//		this->Normal = new Bouton();
//		this->Difficile = new Bouton();
//
//	}
//
//	bool obtActif(void) {
//		return Actif;
//	}
//
//	void defActif(bool Actif) {
//		this->Actif = Actif;
//	}
//
//
//};