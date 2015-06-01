#pragma once
#include "ObjetFixe.h"

class PlafondTueur : public ObjetFixe{
private:
	Vecteur3d posPlafInitiale;
public:
	PlafondTueur(gfx::Modele3D* modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif) : ObjetFixe(modele, ID, materiaux, position, vitesseAngulaire, collisionInterne, interactif){
		this->porte = false;
		this->posPlafInitiale = position;
	}

	Vecteur3d obtPositionInitiale(){

		return posPlafInitiale;

	}



};