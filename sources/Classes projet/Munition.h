#pragma once
#include "Item.h"

class Munition : public Item{
	int quantite;
	virtual void recharger(Joueur* joueur) = 0;
public:
	Munition(int quantite, int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, double masse) : Item(type, nom, description, cheminIcone, INT_MAX, modele, ID, "metal", masse){
		this->quantite = quantite;
	}
	void utiliser(Joueur* joueur){
		recharger(joueur);
	}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
	void animer(Joueur* joueur){}

	int obtQuant(){ return quantite; }
};