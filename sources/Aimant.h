#pragma once
#include "Objet.h"
#include <list>
#include "Physique.h"

class Aimant : public Objet{
private:

	double force;

public:

	Aimant(gfx::Modele3D, modele, unsigned int ID, Vecteur3d position, double force) : Objet(modele, ID, "metaux", 0., vitesse, position){
		this->force = force;
	}
	
	void appliquerPhysique(std::list<Objet*> objets) {
		for (auto it : objets) {
			if (it->obtMasse() != 0) {
				Physique::obtInstance().appliquerMagnetisme(*it, obtModele3D().obtPosition(), force);
			}
		}
	}

	void defForce(double force){
		this->force = force;
	}

	double obtForce(){
		return force;
	}
};