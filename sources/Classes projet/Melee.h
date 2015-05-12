#pragma once
#include "Item.h"

class Melee : public Item{
private:
	double portee, degats;
public:
	Melee(double portee, double degats, int type, char* nom, char* description, char* cheminIcone, int maxPile, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse) : Item(type, nom, description, cheminIcone, maxPile, modele, ID, materiaux, masse){
		this->portee = portee;
		this->degats = degats;
	}
	void utiliser(){

	}
	void equiper(){

	}
};