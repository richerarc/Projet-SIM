#pragma once
#include "Vecteur3.h"

class Joueur {
private:
	double hauteur;
	double rayon;
	gfx::Modele3D modele3D;
	bool accroupie;

public:
	Joueur(gfx::Modele3D modele3D) {
		hauteur = 1.80;
		rayon = 0.25;
		this->modele3D = modele3D;
	}

	double obtHauteur() {
		return hauteur;
	}

	double obtRayon() {
		return rayon;
	}

	gfx::Modele3D obtModele3D() {
		return modele3D;
	}

	void accroupie() {
		hauteur = 1.00;
	}

	void debout() {
		hauteur = 1.80;
	}
};