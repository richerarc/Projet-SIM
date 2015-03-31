#pragma once
#include "Objet.h"
#include <list>
#include "Physique.h"
#include "Vecteur3.h"

class Vent : public Objet{
private:

	Vecteur3d dimensions;

public:

	Vent(Vecteur3d vitesse, unsigned int ID, Vecteur3d position, Vecteur3d dimensions) : Objet(gfx::Modele3D(), ID, "air", 0., vitesse, position){
		this->dimensions.x = dimensions.x;
		this->dimensions.y = dimensions.y;
		this->dimensions.z = dimensions.z;
	}

	void appliquerPhysique(std::list<Objet*> objets) {
		for (auto it : objets) {
			if (it->obtMasse() != 0) {
				if (it->obtModele3D().obtPosition().x >= obtModele3D().obtPosition().x && it->obtModele3D().obtPosition().x <= obtModele3D().obtPosition().x + dimensions.x) {
					if (it->obtModele3D().obtPosition().y >= obtModele3D().obtPosition().y && it->obtModele3D().obtPosition().y <= obtModele3D().obtPosition().y + dimensions.y) {
						if (it->obtModele3D().obtPosition().z >= obtModele3D().obtPosition().z && it->obtModele3D().obtPosition().z <= obtModele3D().obtPosition().z + dimensions.z) {
							Physique::obtInstance().appliquerVent(vitesse, *it);
						}
					}
				}
			}
		}
	}
};