#pragma once
#include "Objet.h"
#include <list>
#include "Physique.h"

class ObjetPhysique : public Objet{
public:

	ObjetPhysique(gfx::Modele3D modele, unsigned int ID, char* materiaux,double masse, Vecteur3d position) : Objet(modele, ID, materiaux, masse, Vecteur3d(0., 0., 0.), position){}

	void appliquerPhysique(std::list<Objet*> objets) {
		Physique::obtInstance().appliquerGravite(vitesse);
	}
};