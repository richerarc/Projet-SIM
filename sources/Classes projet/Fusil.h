#pragma once 
#include "Item.h"
#include "Carte.h"

class Fusil : public Item{
private:
	float ballesParSeconde;
	float degat;
	float angleMaximalEtendue;
	bool recul;
	
public:
	Fusil(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, float ballesParSeconde, float degat, float angleMaximalEtendue, bool recul) : Item(type, nom, description, cheminIcone, 1, modele, 0, materiaux, masse){
		this->ballesParSeconde = ballesParSeconde;
		this->degat = degat;
		this->angleMaximalEtendue = angleMaximalEtendue;
		this->recul = recul;
	}

	void utiliser(){
		Droite rayon(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition(), gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant());
		for (auto &it : Carte::obtInstance().salleActive->obtListeObjet()){
			Vecteur3d pointCollision;
			Vecteur3d normale;
			if (Physique::obtInstance().collisionDroiteModele(it->obtModele3D(), rayon, pointCollision, normale, false)){
				std::cout << pointCollision.x << ", " << pointCollision.y << ", " << pointCollision.z << std::endl;
				std::cout << normale.x << ", " << normale.y << ", " << normale.z << std::endl;
				gfx::Gestionnaire3D::obtInstance().ajouterTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("trouDeBalle.png"), pointCollision, normale);
				
			}
		}
	}

	void equiper(){

	}

};