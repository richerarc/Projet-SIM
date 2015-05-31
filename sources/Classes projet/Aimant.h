#pragma once
#include "Objet.h"
#include "Modele3D.h"
#include <list>

class Aimant : public ObjetPhysique{
private:

	double force;

public:
	Aimant(gfx::Modele3D* modele, unsigned int ID, Vecteur3d position, double force) : Objet(modele, ID, "metal", 0., Vecteur3d(0.f, 0.f, 0.f), position, Vecteur3d(0.,0.,0.), false){
		this->force = force;
	}

	void defForce(double force){
		this->force = force;
	}

	double obtForce(){
		return force;
	}
};