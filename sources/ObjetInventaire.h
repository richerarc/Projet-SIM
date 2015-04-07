#pragma once
#include "Objet.h"
#include <list>


class ObjetInventaire : public Objet{
protected:
	unsigned int quantite;
	bool equipable;
	bool utilisable;
	bool dansInventaire;
public:

	ObjetInventaire(gfx::Modele3D modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool equipable, bool utilisable, bool dansInventaire, unsigned int quantite) : Objet(modele, ID, materiaux, masse, vitesse, position, vitesseAngulaire, false){
		this->quantite = quantite;
	}

	void appliquerAction(typeAction action){
		//actions ici
	}
	void defQuantite(unsigned int quantite){
		this->quantite = quantite;
	}
	void defEquipable(bool equipable){
		this->equipable = equipable;
	}
	void defUtilisable(bool utilisable){
		this->utilisable = utilisable;
	}
	void defDansInventaire(bool dansInventaire){
		this->dansInventaire = dansInventaire;
	}
	bool obtdansInventaire(){
		return dansInventaire;
	}
	bool obtUtilisable(){
		return utilisable;
	}
	bool obtEquipable(){
		return equipable;
	}
	unsigned int obtQuantite(){
		return quantite;
	}
};