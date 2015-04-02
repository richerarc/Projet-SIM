#pragma once
#include "Vecteur3.h"
#include "Objet.h"

class Joueur : public Objet{
private:
	gfx::Modele3D modele3D;
	bool accroupie;

public:
	Joueur(gfx::Modele3D &modele3D, unsigned int ID, double masse, Vecteur3d position) : Objet(modele3D, ID, NULL, masse, NULL, position){
		this->modele3D = modele3D;
	}

	void appliquerPhysique(Salle &salle, double &frametime) {
		if (!Physique::obtInstance().collisionJoueurSalle(*this, salle)) {
			Physique::obtInstance().appliquerGravite(vitesse);
		}
		defPosition(position + (vitesse * frametime));
	}

	gfx::Modele3D obtModele3D() {
		return modele3D;
	}
};