#pragma once
#include "Objet.h"
#include <list>
#include "Physique.h"
#include "ObjetInteractif.h"

class ObjetInventaire : public ObjetInteractif{
private:
	unsigned int quantite;
public:

	ObjetInventaire(gfx::Modele3D modele, unsigned int ID, char* materiaux, double masse, Vecteur3d position, typeObjet type, unsigned int quantite) : ObjetInteractif(modele, ID, materiaux, masse, position, type){
		this->quantite = quantite;
	}

	void appliquerAction(typeAction action){
		switch (type){
		case Couteau :
			switch (action){
			case Utiliser:
				break;
			}
			break;
		}
	}

	unsigned int obtQuantite(){
		return quantite;
	}

	void defQuantite(unsigned int quantite){
		this->quantite = quantite;
	}
};