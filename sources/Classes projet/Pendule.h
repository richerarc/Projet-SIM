#pragma once
#include "ObjetFixe.h"

class Pendule : public ObjetFixe{
private:
	double constantePhase;
	double angleMax;
public:
	Pendule(gfx::Modele3D* modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif, double constantePhase, double angleMax) : ObjetFixe(modele, ID, materiaux, position, vitesseAngulaire, collisionInterne, interactif){
		this->constantePhase = constantePhase;
		this->angleMax = angleMax;
		this->porte = false;
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

	double obtConstantePhase(){
		return constantePhase;
	}

	double obtAngleMax(){
		return angleMax;
	}

};