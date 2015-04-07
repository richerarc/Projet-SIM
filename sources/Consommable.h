#pragma once
#include "ObjetInventaire.h"

class Consommable : public ObjetPhysique{
private:
	char* type;
	unsigned int valeur;
public:
	Consommable(gfx::Modele3D modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool ramassable, unsigned int quantite, bool equipable, bool utilisable, bool dansInventaire, char* type, unsigned int valeur) : ObjetPhysique(modele, ID, materiaux, masse, vitesse, position, vitesseAngulaire, collisionInterne, ramassable, quantite, equipable, utilisable, dansInventaire){
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