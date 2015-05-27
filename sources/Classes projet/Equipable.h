#pragma once
#include "Item.h"

class MasqueGaz : public Item{
	bool etatEquipe;
public:
	MasqueGaz(unsigned int ID) : Item(50, "Gaz Mask", "Your key to get away alive", "Ressources/Texture/masqueAGazIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/masqueAGaz.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/masqueAGaz.png")), ID, "metal", 2.0){
		etatEquipe = false;
	}
	void utiliser(Joueur* joueur){}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
	void animer(Joueur* joueur) {}
};