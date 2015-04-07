#pragma once
#include "Objet.h"

class ObjetFixe : public Objet{
private:
	bool interactif;
public:
	ObjetFixe(gfx::Modele3D& modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif) : Objet(modele, ID, materiaux, 0, Vecteur3d(0., 0., 0.), position, vitesseAngulaire, collisionInterne){
		this->interactif = interactif;
	}

	void appliqueAction(typeAction action){
		//actions ici
	}
	void appliquerPhysique(std::list<Objet*> objets){
		//physique ici
	}

	void defInteraction(bool interactif){
		this->interactif = interactif;
	}

	bool obtInteraction(){
		return this->interactif;
	}
};