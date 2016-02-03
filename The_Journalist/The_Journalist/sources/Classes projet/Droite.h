#pragma once

#include "Vecteur3.h"

class Droite {
private:
	Vecteur3d point;
	Vecteur3d vecteurDirecteur;
public:

	Droite() {}

	Droite(Vecteur3d point, Vecteur3d vecteurDirecteur) {
		this->vecteurDirecteur = vecteurDirecteur;
		this->vecteurDirecteur.normaliser();
		this->point = point;
	}

	Vecteur3d obtenirPoint() {
		return point;
	}

	Vecteur3d& obtenirVecteurDirecteur() {
		return vecteurDirecteur;
	}
};
