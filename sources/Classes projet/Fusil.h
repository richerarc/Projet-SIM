#pragma once 
#include "Item.h"
#include "Carte.h"

enum Ammo { ACP45, PARABELUM };

class Fusil : public Item{
private:
	float ballesParSeconde;
	float degat;
	float angleMaximalEtendue;
	bool recul;
	
public:
	Fusil(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, float ballesParSeconde, float degat, float angleMaximalEtendue, bool recul, int chargeur) : Item(type, nom, description, cheminIcone, 1, modele, 0, materiaux, masse){
		this->ballesParSeconde = ballesParSeconde;
		this->degat = degat;
		this->angleMaximalEtendue = angleMaximalEtendue;
		this->recul = recul;
	}

	void utiliser(){
		Droite rayon(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition(), gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant());
		Vecteur3d pointCollision;
		Vecteur3d normale;
		for (auto &it : Carte::obtInstance().salleActive->obtListeObjet()){
			if (Physique::obtInstance().collisionDroiteModele(it->obtModele3D(), rayon, pointCollision, normale, nullptr, false)){
				gfx::Gestionnaire3D::obtInstance().ajouterTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/trouDeBalle.png"), pointCollision, normale);
			}
		}
		if (Physique::obtInstance().collisionDroiteModele(Carte::obtInstance().salleActive->obtModele(), rayon, pointCollision, normale, nullptr, false)){
			gfx::Gestionnaire3D::obtInstance().ajouterTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/trouDeBalle.png"), pointCollision, normale);
		}
	}

	void utiliser2(){

	}

	void equiper(){

	}

};