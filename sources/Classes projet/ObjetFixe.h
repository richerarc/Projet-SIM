#pragma once
#include "Objet.h"

class ObjetFixe : public Objet{
protected:
	bool interactif;
	bool porte;
public:
	ObjetFixe(gfx::Modele3D* modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif) : Objet(modele, ID, materiaux, 0, Vecteur3d(0., 0., 0.), position, vitesseAngulaire, collisionInterne){
		this->interactif = interactif;
	}

	void defInteraction(bool interactif){
		this->interactif = interactif;
	}

	bool obtInteraction(){
		return this->interactif;
	}

	bool obtSiPorte(){
		return this->porte;
	}
};