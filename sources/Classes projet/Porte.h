#pragma once
#include "ObjetFixe.h"

class Porte : public ObjetFixe{
private:
	bool verrouillee;
	bool parcourue;
public:
	Porte(gfx::Modele3D& modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif, bool verrouillee, bool parcourue) : ObjetFixe(modele, ID, materiaux, position, vitesseAngulaire, collisionInterne, interactif){
		this->verrouillee = verrouillee;
		this->parcourue = parcourue;
	}

	void defVerrouillee(bool verrouillee){
		this->verrouillee = verrouillee;
	}

	void defParcourue(bool parcourue){
		this->parcourue = parcourue;
	}

	bool obtVerrouillee(){
		return verrouillee;
	}

	bool obtParcourue(){
		return parcourue;
	}
};