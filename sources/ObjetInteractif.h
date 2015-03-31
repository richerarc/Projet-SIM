#pragma once
#include "Objet.h"
#include <list>
#include "Physique.h"

class ObjetInteractif : public Objet{
private:
	bool equipe;
public:

	ObjetInteractif(gfx::Modele3D modele, unsigned int ID, char* materiaux,double masse, Vecteur3d position, typeObjet type) : Objet(modele, ID, materiaux, masse, Vecteur3d(0., 0., 0.), position,type){
		equipe = true;
	}

	void appliquerPhysique(std::list<Objet*> objets) {
		Physique::obtInstance().appliquerGravite(vitesse);
	}

	bool obtEquipe(){
		return equipe;
	}

	void defEquipe(bool equipe){
		this->equipe = equipe;
	}
};