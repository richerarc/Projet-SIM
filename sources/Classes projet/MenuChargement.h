#pragma once
#include "Menu.h"
#include "BarreProgressive.h"

class MenuChargement : public Menu {

private:

	gfx::BarreProgressive* barreProgression;

public:

	MenuChargement() {
		barreProgression = new gfx::BarreProgressive(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/BarreProgressive.png"), { 128, 128, 128, 255 }, Vecteur2f(300, 200));
		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/fondMenu.png"));
		defPause(true);
	}

	void actualiserChargement(float pourcentage) {
		barreProgression->rafraichir(pourcentage);
	}

	void remplir() {
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, barreProgression });
	}
	void defPause(bool pause) {

	}
	void actualiserEchelle(Vecteur2f vecteurEchelle){

	}

};