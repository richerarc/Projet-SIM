#pragma once
#include "Item.h"
#include "Peinture.h"

class Melee : public Item{
protected:
	double portee;
	int degats;
	Chrono dps;

	int animationActuelle;
	Chrono animationMelee;
public:
	Melee(double portee, int degats, int type, char* nom, char* description, char* cheminIcone, int maxPile, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse) : Item(type, nom, description, cheminIcone, maxPile, modele, ID, materiaux, masse){
		this->portee = portee;
		this->degats = degats;
	}
	void animer(Joueur* joueur){
		float vitesseJoueur = joueur->obtVitesseDeplacement();
		if (vitesseJoueur == 4.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 3 * sin(10 * animation.obtTempsEcoule().enSecondes()));
		if (vitesseJoueur == 10.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 20 * sin(10 * animation.obtTempsEcoule().enSecondes()));

		if (animationActuelle == 0)
			return;
		if (animationActuelle == 1){
			double tempsMax = 0.4;
			double tempsEcoule = animationMelee.obtTempsEcoule().enSecondes();
			if (tempsEcoule < tempsMax){
				modele->rotationner(Vecteur3d(0, 0, 1), 12500 * tempsEcoule * (tempsEcoule - tempsMax) * (tempsEcoule - 2 * tempsMax / 3));
			}
			else{
				animationMelee.repartir();
				animationActuelle = 0;
			}
		}
	}

	void utiliser(Joueur* joueur){
		if (dps.obtTempsEcoule().enSecondes() > 0.4){
			dps.repartir();
			Droite rayon(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition(), gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant());
			Vecteur3d pointCollision;
			Vecteur3d normale;
			if (Physique::obtInstance().collisionDroiteModele(salleActive->obtModele(), rayon, pointCollision, normale, nullptr, false)){
				if (Maths::distanceEntreDeuxPoints(pointCollision, gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition()) < portee){
					Peinture* trou = new Peinture(123, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/trouDeMelee.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/trouDeMelee.png")), pointCollision, normale);
					salleActive->ajoutObjet(trou);
					gfx::Gestionnaire3D::obtInstance().ajouterObjet(trou->obtModele3D());
					ControlleurAudio::obtInstance().jouer(COUPCOUTEAU, joueur);
				}
				else{
					ControlleurAudio::obtInstance().jouer(COUPCOUTEAUVIDE, joueur);
				}
			}
			animationActuelle = 1;
			animationMelee.repartir();
		}
	}

	virtual void utiliser2(Joueur* joueur){

	}

	virtual void equiper(Joueur* joueur){
		ControlleurAudio::obtInstance().jouer(EQUIPERCOUTEAU, joueur);
	}

	void reinitialiserListePeinture() {}
};