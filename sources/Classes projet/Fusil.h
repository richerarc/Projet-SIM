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

	Chrono animationFusil;
	int animationActuelle;
	
public:
	Fusil(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, float ballesParSeconde, float degat, float angleMaximalEtendue, bool recul, int chargeur, bool automatique) : Item(type, nom, description, cheminIcone, 1, modele, ID, materiaux, masse){
		this->ballesParSeconde = ballesParSeconde;
		this->degat = degat;
		this->angleMaximalEtendue = angleMaximalEtendue;
		this->recul = recul;
	}

	void animer(){
		if (animationActuelle == 0)
			return;
		if (animationActuelle == 1){
			double tempsMax = 1 / ballesParSeconde;
			double tempsEcoule = animationFusil.obtTempsEcoule().enSecondes();
			if (tempsEcoule < tempsMax){
				angleAnimation = 2500 * tempsEcoule * (tempsEcoule - tempsMax) * (tempsEcoule - 2 * tempsMax / 3);
			}
			else{
				animationFusil.repartir();
				animationActuelle = 0;
			}
		}

	}

	void utiliser(Joueur* joueur){
		if (dps.obtTempsEcoule().enSecondes() > 1 / ballesParSeconde){
			Droite rayon(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition(), gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant());
			Vecteur3d pointCollision;
			Vecteur3d normale;
			animationActuelle = 1;
			animationFusil.repartir();
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