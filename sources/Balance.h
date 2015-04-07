#pragma once
#include "ObjetFixe.h"

class Balance : public ObjetFixe{
private:
	gfx::Modele3D& modeleBarre;
public:
	Balance(gfx::Modele3D& modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif, gfx::Modele3D& modeleBarre) : ObjetFixe(modele, ID, materiaux, position, vitesseAngulaire, collisionInterne, interactif){
		this->modeleBarre = modeleBarre;
	}

	gfx::Modele3D& obtModeleBarre(){
		return modeleBarre;
	}

	double obtAngle(){
		//Fill in later.
	}
};