#pragma once 
#include "Item.h"

class Jetable : public Item{

public:
	Jetable(int type, char* nom, char* description, char* cheminIcone, int maxPile, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse) : Item(type, nom, description, cheminIcone, maxPile, modele, ID, materiaux, masse){
	
	}
	virtual void animer(Joueur* joueur){}
	void utiliser(Joueur* joueur){
		this->defEtat(EtatItem::DEPOSE);
		this->defVitesse(joueur->obtDevant() * 10);
		joueur->obtInventaire()->retirerObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
	}
	virtual void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
};