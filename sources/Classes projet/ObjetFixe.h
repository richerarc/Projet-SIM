#pragma once
#include "Objet.h"

class ObjetFixe : public Objet{
private:
	bool interactif;
public:
	ObjetFixe(gfx::Modele3D* modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif) : Objet(modele, ID, materiaux, 0, Vecteur3d(0., 0., 0.), position, vitesseAngulaire, collisionInterne){
		this->interactif = interactif;
	}

	void appliquerAction(typeAction action){
		if (interactif){
			switch (action){
			case Interagir:
				break;
			case Osciller:
				break;
			}
		}
	}

	void defInteraction(bool interactif){
		this->interactif = interactif;
	}

	bool obtInteraction(){
		return this->interactif;
	}
};