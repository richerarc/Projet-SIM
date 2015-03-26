#pragma once
#include "Vecteur3.h"
#include "Objet.h"

class Joueur : public Objet{
private:
	double hauteur;
	double rayon;
	gfx::Modele3D modele3D;
	bool accroupie;

public:
	Joueur(gfx::Modele3D &modele3D, unsigned int ID, double masse, Vecteur3d position) : Objet(modele3D, ID, NULL, masse, NULL, position) {
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