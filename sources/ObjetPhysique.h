#pragma once
#include "Objet.h"
#include <list>

class ObjetPhysique : public Objet{
private :
	bool ramassable;
public:

	ObjetPhysique(gfx::Modele3D modele, unsigned int ID, char* materiaux,double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool ramassable) : Objet(modele, ID, materiaux, masse, vitesse, position, vitesseAngulaire,collisionInterne){
		this->ramassable = ramassable;
	}

	void appliquerAction(typeAction action){
		//appliquer une action sur l'objet ici
	}

	void defRamassable(bool ramassable){
		this->ramassable = ramassable;
	}

	bool obtRamassable(){
		return ramassable;
	}
};