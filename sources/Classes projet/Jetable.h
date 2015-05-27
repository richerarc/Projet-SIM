#pragma once 
#include "Item.h"

struct Jetable : public Item{
	Jetable(int type, char* nom, char* description, char* cheminIcone, int maxPile, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse) : Item(type, nom, description, cheminIcone, maxPile, modele, ID, materiaux, masse){

	}
	~Jetable(){

	}
	virtual void animer(Joueur* joueur){

	}
	void utiliser(Joueur* joueur){
		this->defEtat(EtatItem::DEPOSE);
		this->defVitesse(joueur->obtDevant() * 50);
		joueur->obtInventaire()->retirerObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
	}
	virtual void utiliser2(Joueur* joueur){
		this->defEtat(EtatItem::DEPOSE);
		this->defVitesse(joueur->obtDevant() * 20);
		joueur->obtInventaire()->retirerObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
	}
	void equiper(Joueur* joueur){}
};