#pragma once
#include "Item.h"
#include "ControlleurAudio.h"
#include "Texte2D.h"
#include "GestionnaireRessources.h"

class Illuminati : public Item{
private:
	gfx::Texte2D* texteIllumination;
public:

	Illuminati(unsigned int ID) : Item(80, "Triangle of the illumination", "Is this real life?", "Ressources/Texture/illuminatiIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/trouDeBalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/illuminati.png")), ID, "metal", 10){

	}

	void utiliser(Joueur* joueur){

	}

	void utiliser2(Joueur* joueur){

	}

	void equiper(Joueur* joueur){

	}

	void animer(Joueur* joueur){
		
	}
};