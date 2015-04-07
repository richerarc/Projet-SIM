#pragma once
#include "ObjetFixe.h"

class Balance : public ObjetFixe{
public:
	Balance(gfx::Modele3D& modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif) : ObjetFixe(gfx::Modele3D& modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif){}

	double obtAngle(){
		//Fill in later.
	}
};