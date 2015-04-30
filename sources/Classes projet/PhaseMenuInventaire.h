#pragma once 
#include "Phase.h"
#include "MenuInventaire.h"
#include "MenuAccesRapide.h"

class PhaseMenuInventaire : public Phase{
private:

	MenuInventaire* menu;

public:

	PhaseMenuInventaire(Inventaire* inventaire) : Phase(){
		menu = new MenuInventaire(inventaire);
	}

	~PhaseMenuInventaire() {
		delete menu;
	}

	void rafraichir(float frameTime) {
	}

	void remplir() {
		menu->remplir();
	}
	void defPause(bool pause) {
		menu->defPause(pause);
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menu->actualiserEchelle(vecteurEchelle);
	}
};