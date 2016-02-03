#pragma once
#include "Phase.h"
#include "MenuChargement.h"

class PhaseMenuChargement : public Phase{

private:

	MenuChargement* menuChargement;

public:

	PhaseMenuChargement() {
		menuChargement = new MenuChargement();
	}

	void actualiserChargement(float pourcentage) {
		menuChargement->actualiserChargement(pourcentage);
	}

	void rafraichir(float frameTime) {
		
	}

	void remplir(){
		menuChargement->remplir();
	}

	void defPause(bool pause){
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle){
		
	}
};