#pragma once
#include "Item.h"

class Note : public Item {

public:

	Note(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse) : Item(type, nom, description, cheminIcone, 1, modele, 21, materiaux, masse){

	}

	void utiliser(){

	}

	void equiper(){

	}

};