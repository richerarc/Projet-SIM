#pragma once
#include "Objet.h"
#include <list>

class ObjetPhysique : public Objet{
private :
	bool ramassable;
	unsigned int quantite;
	bool equipable;
	bool utilisable;
	bool dansInventaire;
public:

	ObjetPhysique(gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool ramassable, unsigned int quantite, bool equipable, bool utilisable,bool dansInventaire) : Objet(modele, ID, materiaux, masse, vitesse, position, vitesseAngulaire, collisionInterne){
		this->ramassable = ramassable;
		this->quantite = quantite;
		this->equipable = equipable;
		this->utilisable = utilisable;
		this->dansInventaire = dansInventaire;
	}
	void appliquerAction(typeAction action){
		//appliquer une action sur l'objet ici
	}
	void defRamassable(bool ramassable){
		this->ramassable = ramassable;
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
	bool obtRamassable(){
		return ramassable;
	}
};