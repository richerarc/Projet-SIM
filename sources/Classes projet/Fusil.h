#pragma once 
#include "Item.h"
#include "Peinture.h"

class Fusil : public Item{
private:
	float ballesParSeconde;
	float degat;
	float angleMaximalEtendue;
	float recul;
	short chargeur, munition;
	bool automatique;
	bool dernierCoup;

	Chrono dps;

	Chrono animationFusil;
	int animationActuelle;

public:
	Fusil(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, float ballesParSeconde, float degat, float angleMaximalEtendue, float recul, short chargeur, bool automatique) : Item(type, nom, description, cheminIcone, 1, modele, ID, materiaux, masse){
		this->ballesParSeconde = ballesParSeconde;
		this->degat = degat;
		this->angleMaximalEtendue = angleMaximalEtendue;
		this->recul = recul;
		this->automatique = automatique;
		this->chargeur = chargeur;
		munition = rand() % 3;
	}

	void animer(Joueur* joueur){
		dernierCoup = Souris::boutonAppuye(SDL_BUTTON_LEFT);
		if (!Souris::boutonAppuye(SDL_BUTTON_RIGHT))
			angleHorizontal = 80;

		float vitesseJoueur = joueur->obtVitesseDeplacement();
		if (vitesseJoueur == 4.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 3 * sin(10 * animation.obtTempsEcoule().enSecondes()));
		if (vitesseJoueur == 10.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 20 * sin(10 * animation.obtTempsEcoule().enSecondes()));

		if (animationActuelle == 0)
			return;
		if (animationActuelle == 1){
			double tempsMax = 1 / ballesParSeconde;
			double tempsEcoule = animationFusil.obtTempsEcoule().enSecondes();
			if (tempsEcoule < tempsMax){
				modele->rotationner(Vecteur3d(0, 0, 1), ballesParSeconde * -2500 * tempsEcoule * (tempsEcoule - tempsMax) * (tempsEcoule - 2 * tempsMax / 3));
			}
			else{
				animationFusil.repartir();
				animationActuelle = 0;
			}
		}
	}

	void utiliser(Joueur* joueur){
		if (!automatique || dernierCoup){
			dernierCoup = Souris::boutonAppuye(SDL_BUTTON_LEFT);
			return;
		}

		if (dps.obtTempsEcoule().enSecondes() > 1 / ballesParSeconde){
			dps.repartir();
			--munition;
			if (type == 10)
				ControlleurAudio::obtInstance().jouer(COUPLUGER, joueur);
			if (type == 11)
				ControlleurAudio::obtInstance().jouer(COUPTHOMPSON, joueur);

			double s = double(rand() % 100) / 100;
			double r = double(rand() % 100) / 100;

			double h = cos(Maths::degreARadian(angleMaximalEtendue));

			double phi = 2 * M_PI * s;
			double z = h + (1 - h) * r;
			double sinT = sqrt(1 - z * z);
			double x = cos(phi) * sinT;
			double y = sin(phi) * sinT;

			Vecteur3d nouveauRayon = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtCote() * x + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut() * y + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant() * z;
			nouveauRayon.normaliser();

			Droite rayon(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition(), nouveauRayon);
			Vecteur3d pointCollision;
			Vecteur3d normale;
			animationActuelle = 1;
			animationFusil.repartir();
			for (auto &it : salleActive->obtListeObjet()){
				if (dynamic_cast<Peinture*>(it))
					continue;
				if (Physique::obtInstance().collisionDroiteModele(it->obtModele3D(), rayon, pointCollision, normale, false)){

					if (it->obtMateriaux() == "personnage"){
						salleActive->retirerObjet(it);
						delete it;
						ControlleurAudio::obtInstance().jouer(AH, joueur);
						break;
					}
					else{
						Peinture* trou = new Peinture(123, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/trouDeBalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/trouDeBalle.png")), pointCollision, normale, false);
						salleActive->ajoutObjet(trou);
						gfx::Gestionnaire3D::obtInstance().ajouterObjet(trou->obtModele3D());
						if (dynamic_cast<Item*>(it)){
							Vecteur3d poussee = nouveauRayon * (1 / (degat * it->obtMasse()));
							poussee.y = 0;
							it->defVitesse(poussee);
						}
					}
				}
				if (Physique::obtInstance().collisionDroiteModele(salleActive->obtModele(), rayon, pointCollision, normale, false)){
					Peinture* trou = new Peinture(123, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/trouDeBalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/trouDeBalle.png")), pointCollision, normale, false);
					salleActive->ajoutObjet(trou);
					gfx::Gestionnaire3D::obtInstance().ajouterObjet(trou->obtModele3D());
				}
				gfx::Gestionnaire3D::obtInstance().obtCamera()->defVAngle(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtVAngle() + recul);
				double hRecul = (rand() % int(recul * 100) - (recul * 50)) / 100;
				gfx::Gestionnaire3D::obtInstance().obtCamera()->defHAngle(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHAngle() + hRecul);
			}
		}
	}
	void utiliser2(Joueur* joueur){
		ControlleurAudio::obtInstance().jouer(MIRE, joueur);
		Vecteur3d newPosition = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition() + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant() * 0.4 - gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut() * 0.145;
		if (nom == "Thompson M1")
			newPosition = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition() + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant() * 0.4 - gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut() * 0.32;
		this->position = newPosition;
		modele->defPosition(position);
		angleHorizontal = 90;
	}

	void equiper(Joueur* joueur){
		ControlleurAudio::obtInstance().jouer(EQUIPERFUSIL, joueur);
	}

	void charger(short munition){
		this->munition += munition;
	}

	short obtChargeur(){ return chargeur; }
	short obtballesRestantes() { return munition; }
};