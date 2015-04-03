#pragma once
#include "ObjetInventaire.h"

class ElementCT : public ObjetInventaire{
private:
	char* type;
	unsigned int valeur;
public:
	ElementCT(gfx::Modele3D modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool dansInventaire, unsigned int quantite, char* type, unsigned int valeur) : ObjetInventaire(modele, ID, materiaux, masse, vitesse, position, vitesseAngulaire, false, true, dansInventaire, quantite){
		this->type = type;
		this->valeur = valeur;
	}

	void defType(char* type){
		this->type = type;
	}
	void defValeur(unsigned int valeur){
		this->valeur = valeur;
	}
	unsigned int obtValeur(){
		return valeur;
	}
	char* obtType(){
		return type;
	}
};