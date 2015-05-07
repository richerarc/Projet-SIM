#pragma once
#include "Objet.h"
#include <list>

class ObjetPhysique : public Objet{
public:
	ObjetPhysique(gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne) : Objet(modele, ID, materiaux, masse, vitesse, position, vitesseAngulaire, collisionInterne){}
	
};