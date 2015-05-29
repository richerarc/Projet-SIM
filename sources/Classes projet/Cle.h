#pragma once
#include "Item.h"

class Cle : public Item{
protected:
	int degats;
public:
	Cle(unsigned int ID, int type, char* nom, char* description, char* cheminTexture) : Item(type, nom, description, "Ressources/Texture/cleIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/Clef.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture(cheminTexture)), ID, "metal", 0.3){}
	void utiliser(Joueur* joueur){}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
	void animer(Joueur* joueur){}
};

class CleRoulliee : public Cle{
public:
	CleRoulliee(unsigned int ID) : Cle(ID, 60, "Rusty Key", "At least it's still usable", "Ressources/Texture/cleRoulliee.png"){
		degats = 20;
	}
};

class CleFer : public Cle{
public:
	CleFer(unsigned int ID) : Cle(ID, 61, "Iron Key", "A pretty nice key", "Ressources/Texture/cleFer.png"){
		degats = 80;
	}
};

class CleFinale : public Cle{
public:
	CleFinale(unsigned int ID) : Cle(ID, 62, "Final Key", "The only key that will open your way out", "Ressources/Texture/cleFinale.png"){
		degats = INT_MAX;
	}
};