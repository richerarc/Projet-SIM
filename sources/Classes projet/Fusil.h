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
	Fusil(char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, float ballesParSeconde, float degat, float angleMaximalEtendue, bool recul) : Item(1, nom, description, cheminIcone, 1, modele, 0, materiaux, masse, Vecteur3d(), Vecteur3d(), Vecteur3d(), false){
		this->ballesParSeconde = ballesParSeconde;
		this->degat = degat;
		this->angleMaximalEtendue = angleMaximalEtendue;
		this->recul = recul;
	}

	void utiliser(){
		Droite rayon(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition(), gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant());
		for (auto &it : Carte::obtInstance().salleActive->obtListeObjet()){
			Vecteur3d pointCollision;
			if (Physique::obtInstance().collisionDroiteModele(it->obtModele3D(), rayon, pointCollision, Vecteur3d(), false)){
				if (!pointCollision == Vecteur3d()){

				}
			}
		}
	}

	void equiper(){

	}

};