#pragma once
#include "Item.h"
#include "Texte2D.h"

class Note : public Item {

private:

	gfx::Texte2D* code;

	int animationActuelle;

	bool dernierCoup;

public:

	Note(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse) : Item(type, nom, description, cheminIcone, 1, modele, 21, materiaux, masse){

		this->code = new gfx::Texte2D();

	}

	void animer(Joueur* joueur){
		
	}

	void utiliser(){

	}

	void utiliser2(){


	}

	void equiper(){

	}

	void defcode(std::string* texte) {
		code->defTexte(texte);
	}

};