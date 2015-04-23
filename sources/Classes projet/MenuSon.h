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

		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));
		volumeJeu = new gfx::Texte2D("Game sound", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial50", 50), Vecteur2f(100, 500));

		volume = new Glisseur(Vecteur2f(100, 400), Vecteur2f(1,1), 50);

	}

	void remplir(void) {

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, volumeJeu });
		volume->remplir();

	}

	void defPause(bool pause) {



	}

};