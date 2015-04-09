#pragma once
#include "Objet.h"
#include "Modele3D.h"
#include <list>

class Aimant : public Objet{
private:

	double force;

public:
	Aimant(gfx::Modele3D* modele, unsigned int ID, Vecteur3d position, double force) : Objet(modele, ID, "metal", 0., Vecteur3d(0.f, 0.f, 0.f), position, Vecteur3d(0.,0.,0.), false){
		this->force = force;
	}

	void appliquerAction(typeAction action){
		//actions ici s'il y a lieu
	}

	void defForce(double force){
		this->force = force;
	}

	double obtForce(){
		return force;
	}
};