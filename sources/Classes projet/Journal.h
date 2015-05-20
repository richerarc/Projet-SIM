#pragma once
#include "Item.h"
#include "Texte2D.h"

class Journal : public Item {

private:

	gfx::Texte2D* code;

public:

	Journal(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, gfx::Texte2D* code) : Item(type, nom, description, cheminIcone, 1, modele, 20, materiaux, masse){
		
		this->code = new gfx::Texte2D();

	}

	void utiliser(){
		
	}

	void equiper(){

	}

	void defcode(std::string* texte) {
		code->defTexte(texte);
	}

};