#pragma once 
#include "Item.h"
#include "Peinture.h"

enum Ammo { ACP45, PARABELUM };

class Fusil : public Item{
private:
	float ballesParSeconde;
	float degat;
	float angleMaximalEtendue;
	bool recul;
	bool automatique;

	Chrono dps;
	
public:
	Fusil(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, float ballesParSeconde, float degat, float angleMaximalEtendue, bool recul, int chargeur, bool automatique) : Item(type, nom, description, cheminIcone, 1, modele, 0, materiaux, masse){
		this->ballesParSeconde = ballesParSeconde;
		this->degat = degat;
		this->angleMaximalEtendue = angleMaximalEtendue;
		this->recul = recul;
	}

	void utiliser(Joueur* joueur){
		if (dps.obtTempsEcoule().enSecondes() > 1 / ballesParSeconde){
			Droite rayon(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition(), gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant());
			Vecteur3d pointCollision;
			Vecteur3d normale;
			for (auto &it : Carte::obtInstance().salleActive->obtListeObjet()){
				if (Physique::obtInstance().collisionDroiteModele(it->obtModele3D(), rayon, pointCollision, normale, nullptr, false)){
					Peinture* trou = new Peinture(123, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/trouDeBalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/trouDeBalle.png")), pointCollision, normale);
					salleActive->ajoutObjet(trou);
					gfx::Gestionnaire3D::obtInstance().ajouterObjet(trou->obtModele3D());
				}
			}
			if (Physique::obtInstance().collisionDroiteModele(Carte::obtInstance().salleActive->obtModele(), rayon, pointCollision, normale, nullptr, false)){
				Peinture* trou = new Peinture(123, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/trouDeBalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/trouDeBalle.png")), pointCollision, normale);
				salleActive->ajoutObjet(trou);
				gfx::Gestionnaire3D::obtInstance().ajouterObjet(trou->obtModele3D());
			}
			dps.repartir();
		}
	}

	void utiliser2(Joueur* joueur){

	}

	void equiper(Joueur* joueur){

	}

};