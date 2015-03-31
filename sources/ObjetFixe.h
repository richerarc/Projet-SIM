#pragma once
#include "Objet.h"

class ObjetFixe : public Objet{
private:
	bool interactif;
public:
	ObjetFixe(gfx::Modele3D& modele, unsigned int ID, char* materiaux, Vecteur3d position,typeObjet objet, bool interactif) : Objet(modele, ID, materiaux, 0, Vecteur3d(0., 0., 0.), position,objet){
		this->interactif = interactif;
	}

	void AppliqueAction(typeAction action){
		switch (type){
		case Balance:
			switch (action){
			case Osciller:
				break;
			}
			break;
		case Pendule:
			switch (action){
			case Osciller:
				break;
			}
			break;
		}
	}

	void defInteraction(bool interactif){
		this->interactif = interactif;
	}

	bool obtInteraction(){
		return this->interactif;
	}
};