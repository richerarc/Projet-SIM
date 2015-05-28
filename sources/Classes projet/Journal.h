#pragma once
#include "Item.h"
#include "Texte2D.h"

class Journal : public Item {

private:

public:

	Journal(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, gfx::Texte2D* code) : Item(type, nom, description, cheminIcone, 1, modele, 20, materiaux, masse){
		
		

	}

	void utiliser(Joueur* joueur){}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
	void animer(Joueur* joueur){}

};