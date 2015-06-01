#pragma once
#include "ObjetFixe.h"
#include "Cible.h"

class Porte : public ObjetFixe{
private:
	bool verrouillee;
	bool parcourue;
public:
	Porte(gfx::Modele3D* modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif, bool verrouillee, bool parcourue, Cible* cible) : ObjetFixe(modele, ID, materiaux, position, vitesseAngulaire, collisionInterne, interactif){
		this->verrouillee = verrouillee;
		this->parcourue = parcourue;
		this->porte = true;
		this->cible = cible;
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

	Cible* obtCible(void) {
		return cible;
	}

};