#pragma once
#include "Gestionnaire3D.h"
#include "Vecteur3.h"
#include "Plan.h"
#include "GestionnaireControle.h"

enum etat { STABLE, ACCROUPI, MARCHE, SAUT, CHUTE };
enum modele { MODELEDEBOUT, MODELEACCROUPI };

class Joueur {
private:
	gfx::Modele3D* modele3D;
	gfx::Camera* camera;
	gfx::Modele3D* listeModele3D[2];
	gfx::Camera* listeCamera[2];
	Vecteur3d position;
	Vecteur3d vitesse;
	double masse;
	float vitesseDeplacement;
	int etat;
	short santePhysique, santeMentale;
	Vecteur3d normale;
	Vecteur3d pointCollision;
	bool bloque;
	Chrono chronoSaut;

	/*y=-(Ax+Cz+d)/B */
	void ajusterVitesse(){
		Plan plan(pointCollision, normale);
		double B = plan.obtenirNormale().y;
		if (B){
			double A = plan.obtenirNormale().x;
			double x = vitesse.x;
			double C = plan.obtenirNormale().z;
			double z = vitesse.z;
			double d = plan.obtenirD();
			double y = -(((A * x) + (C * z) + d) / B);
			vitesse.y = y;
		}
	}

public:

	Joueur() {}

	Joueur(Vecteur3d position) {
		this->vitesseDeplacement = 4.f;
		this->position = position;
		etat = CHUTE;
		masse = 87.f;
		santePhysique = 100;
		santeMentale = 100;
		vitesse = { 0, 0, 0 };
		bloque = false;
		listeCamera[MODELEDEBOUT] = new gfx::Camera;
		listeCamera[MODELEACCROUPI] = new gfx::Camera;
		listeModele3D[MODELEDEBOUT] = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Joueur.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));
		listeModele3D[MODELEACCROUPI] = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("JoueurAccroupi.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));
		camera = listeCamera[MODELEDEBOUT];
		modele3D = listeModele3D[MODELEDEBOUT];
		listeModele3D[MODELEDEBOUT]->defPosition(position);
		listeModele3D[MODELEACCROUPI]->defPosition(position);
		chronoSaut = Chrono();
	}

	~Joueur() {
		delete listeCamera[0];
		delete listeCamera[1];
		delete listeModele3D[0];
		delete listeModele3D[1];
	}

	void deplacement(){
		if (!bloque){
			if ((Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(AVANCER)) || Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(RECULER)) || Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(GAUCHE)) || Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(DROITE))) && (etat == STABLE || etat == MARCHE || etat == ACCROUPI)){
				vitesse.x = 0.f;
				vitesse.z = 0.f;
				if (vitesse.y == 0){
					etat = STABLE;
					vitesse.y = 0.f;
				}
				etat = STABLE;
			}

			if (etat == CHUTE && vitesse.x == 0 && vitesse.y == 0 && vitesse.z == 0){
				etat = STABLE;
			}


			Vecteur3d devant = camera->obtDevant();
			devant.y = 0;
			Vecteur3d cote = camera->obtCote();
			devant.normaliser();
			cote.y = 0;
			Vecteur3d vitesseTemp;
			if (Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(COURIR)) && (vitesseDeplacement != 4.f) && (camera != listeCamera[MODELEACCROUPI]))
				vitesseDeplacement = 4.f;

			if (etat != SAUT && etat != CHUTE) {
				if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(COURIR)) && (camera != listeCamera[MODELEACCROUPI]) && vitesseDeplacement != 8.f)
					vitesseDeplacement = 8.f;

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(ACCROUPIR)) && (camera != listeCamera[MODELEACCROUPI])) {
					camera = listeCamera[MODELEACCROUPI];
					modele3D = listeModele3D[MODELEACCROUPI];
					ajouterScene();
					vitesseDeplacement = 2.f;
				}

				else if (Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(ACCROUPIR)) && camera != listeCamera[MODELEDEBOUT]) {
					camera = listeCamera[MODELEDEBOUT];
					modele3D = listeModele3D[MODELEDEBOUT];
					ajouterScene();
					etat = STABLE;
					vitesseDeplacement = 4.f;
				}

				/*if ((normale.x != 0 || normale.z != 0) && (normale.y != 0)) {
				vitesseDeplacement = 4.f;
				}*/

				if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(AVANCER))){
					//etat = MARCHE;
					if ((normale.x != 0.f || normale.z != 0.f) || normale == Vecteur3d(0, 0, 0)) {
						vitesse.x = devant.x * vitesseDeplacement;
						vitesse.z = devant.z * vitesseDeplacement;
					}
					else if (normale.x == 0.f && normale.z == 0.f && normale.y != 0.f)
						vitesse = devant * vitesseDeplacement;
					if (vitesseDeplacement < 5) {
						if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(DROITE))) {
							if (normale.x != 0.f || normale.z != 0.f) {
								vitesse.x = vitesse.x + (cote.x * vitesseDeplacement);
								vitesse.z = vitesse.z + (cote.z * vitesseDeplacement);
							}
							else
								vitesse = vitesse + (cote * vitesseDeplacement);
						}

						else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(GAUCHE))) {
							if (normale.x != 0.f || normale.z != 0.f) {
								vitesseTemp.x = cote.x * vitesseDeplacement;
								vitesseTemp.z = cote.z * vitesseDeplacement;
							}
							else
								vitesseTemp = cote * vitesseDeplacement;
							vitesseTemp.inverser();
							if (normale.x != 0.f || normale.z != 0.f) {
								vitesse.x = vitesse.x + vitesseTemp.x;
								vitesse.z = vitesse.z + vitesseTemp.z;
							}
							else
								vitesse = vitesse + vitesseTemp;
						}
					}
					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						//vitesse *= 2;
						if (devant.produitScalaire(tmpNormale) > 0.f) {
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(RECULER))) {
					//etat = MARCHE;
					if ((normale.x != 0.f || normale.z != 0.f) || normale == Vecteur3d(0, 0, 0)) {
						vitesse.x = devant.x * vitesseDeplacement;
						vitesse.z = devant.z * vitesseDeplacement;
					}
					else if (normale.x == 0.f && normale.z == 0.f && normale.y != 0.f)
						vitesse = devant * vitesseDeplacement;
					vitesse.inverser();
					if (vitesseDeplacement < 5) {
						if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(DROITE))) {
							if (normale.x != 0.f || normale.z != 0.f) {
								vitesse.x = vitesse.x + (cote.x * vitesseDeplacement);
								vitesse.z = vitesse.z + (cote.z * vitesseDeplacement);
							}
							else
								vitesse = vitesse + (cote * vitesseDeplacement);
						}
						else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(GAUCHE))) {
							if (normale.x != 0.f || normale.z != 0.f) {
								vitesseTemp.x = cote.x * vitesseDeplacement;
								vitesseTemp.z = cote.z * vitesseDeplacement;
							}
							else
								vitesseTemp = cote * vitesseDeplacement;
							vitesseTemp.inverser();
							if (normale.x != 0.f || normale.z != 0.f) {
								vitesse.x = vitesse.x + vitesseTemp.x;
								vitesse.z = vitesse.z + vitesseTemp.z;
							}
							else
								vitesse = vitesse + vitesseTemp;
						}
					}
					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						//vitesse *= 2;
						if (vitesse.produitScalaire(tmpNormale) > 0.f) {
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(GAUCHE))) {
					//etat = MARCHE;
					if (normale.x != 0.f || normale.z != 0.f) {
						vitesseTemp.x = cote.x * vitesseDeplacement;
						//vitesseTemp.z = cote.z * vitesseDeplacement;
					}
					else
						vitesseTemp = cote * vitesseDeplacement;
					vitesseTemp.inverser();
					if (normale.x != 0.f || normale.z != 0.f) {
						vitesse.x = vitesse.x + vitesseTemp.x;
						vitesse.z = vitesse.z + vitesseTemp.z;
					}
					else
						vitesse = vitesse + vitesseTemp;

					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						//vitesse *= 2;
						if (vitesse.produitScalaire(tmpNormale) > 0.f) {
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(DROITE))){
					//etat = MARCHE;
					if (normale.x != 0.f || normale.z != 0.f) {
						vitesse.x = vitesse.x + (cote.x * vitesseDeplacement);
						vitesse.z = vitesse.z + (cote.z * vitesseDeplacement);
					}
					else
						vitesse = vitesse + (cote * vitesseDeplacement);

					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						//vitesse *= 2;
						if (vitesse.produitScalaire(tmpNormale) > 0.f) {
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
				}

				if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(SAUTER)) && (camera != listeCamera[MODELEACCROUPI])) {
					if ((chronoSaut.obtTempsEcoule().enSecondes() > 1.15))
					{
						chronoSaut.repartir();
						vitesse.y = 7;
						etat = SAUT;
					}
				}
			}
			if (normale.x == 0.f && normale.z == 0.f && normale.y != 0)
				modele3D->defOrientation(0, (camera->obtHAngle()), 0);
		}
	}

	/* by Sam
	void changementSalle(Objet* objet, Joueur& joueur){
	Carte::obtInstance().destination(Entree(Carte::obtInstance().salleActive->obtID(), objet->obtID(), false) joueur);
	}
	*/
	void longer(){
		Vecteur3d direction;
		//x
		if (vitesse.x != 0 && vitesse.y != 0 && vitesse.z != 0){
			if (normale.x != 0.){
				if (normale.x > 0.){
					direction.x = normale.x - 1;
				}
				else {
					direction.x = normale.x + 1;
				}
				if ((vitesse.x < 0. && normale.x > 0.) || (vitesse.x > 0. && normale.x < 0.)){
					if (vitesse.x != direction.x && vitesse.x != direction.x*-1){
						if (vitesse.x < 0.){
							if (!(direction.x < 0.))
								direction.x = direction.x * -1;
						}
						else {
							if (direction.x < 0.)
								direction.x = direction.x * -1;
						}
					}
				}
				vitesse.x = direction.x;
			}

			//y
			if (normale.y != 0.){
				if (normale.y > 0.){
					direction.y = normale.y - 1;
				}
				else {
					direction.y = normale.y + 1;
				}
				if ((vitesse.y < 0. && normale.y > 0.) || (vitesse.y > 0. && normale.y < 0.)){
					if (vitesse.y != direction.y && vitesse.y != direction.y*-1){
						if (vitesse.y < 0.){
							if (!(direction.y < 0.))
								direction.y = direction.y * -1;
						}
						else {
							if (direction.y < 0.)
								direction.y = direction.y * -1;
						}
					}
				}
				vitesse.y = direction.y;
			}

			//z
			if (normale.z != 0.){
				if (normale.z > 0.){
					direction.z = normale.z - 1;
				}
				else {
					direction.z = normale.z + 1;
				}
				if ((vitesse.z < 0. && normale.z > 0.) || (vitesse.z > 0. && normale.z < 0.)){
					if (vitesse.z != direction.z && vitesse.z != direction.z*-1){
						if (vitesse.z < 0.){
							if (!(direction.z < 0.))
								direction.z = direction.z * -1;
						}
						else {
							if (direction.z < 0.)
								direction.z = direction.z * -1;
						}
					}
				}
				vitesse.z = direction.z;
			}

			/////
			/*
			if (normale.x != 0.){
			if ((normale.x > 0. && vitesse.x < 0.) || (normale.x < 0. && vitesse.x > 0.)){
			vitesse.x = 0.;
			}
			}
			//if (normale.y != 0.){
			//if ((normale.y > 0. && vitesse.y < 0.) || (normale.y < 0. && vitesse.y > 0.)){
			//vitesse.y = 0.;
			//}
			//}
			if (normale.z != 0.){
			if ((normale.z > 0. && vitesse.z < 0.) || (normale.z < 0. && vitesse.z > 0.)){
			vitesse.z = 0.;
			}
			}
			*/
		}
	}

	void ajouterScene(){ gfx::Gestionnaire3D::obtInstance().defCamera(camera); }

	void defVitesseY(double y){ this->vitesse.y = y; }

	void defPosition(Vecteur3d pos){
		this->position = pos;
		this->modele3D->defPosition(position);
		listeCamera[MODELEDEBOUT]->defPosition(Vecteur3d(position.x, position.y + 1.74f, position.z));
		listeCamera[MODELEACCROUPI]->defPosition(Vecteur3d(position.x, position.y + 1.00f, position.z));
	}

	void defPositionY(double y) {
		this->position.y = y;
		this->modele3D->defPosition(position);
		listeCamera[MODELEDEBOUT]->defPosition(Vecteur3d(position.x, position.y + 1.74f, position.z));
		listeCamera[MODELEACCROUPI]->defPosition(Vecteur3d(position.x, position.y + 1.00f, position.z));
	}

	void defPointCollision(Vecteur3d pointCollision){
		this->pointCollision = pointCollision;
	}

	void defNormale(Vecteur3d normale){ this->normale = normale; }

	void defAngleHorizontal(double hAngle){
		listeCamera[MODELEDEBOUT]->defHAngle(Maths::degreARadian(hAngle));
		listeCamera[MODELEACCROUPI]->defHAngle(Maths::degreARadian(hAngle));
	}

	gfx::Camera* obtCamera(){ return camera; }

	void defEtat(unsigned int etat){ if (etat <= 5) this->etat = etat; }

	void bloquer(){
		this->bloque = true;
		listeCamera[MODELEDEBOUT]->bloquer();
		listeCamera[MODELEACCROUPI]->bloquer();
		//gfx::Gestionnaire3D::obtInstance().obtCamera()->bloquer();
	}

	void deBloquer(){
		this->bloque = false;
		listeCamera[MODELEDEBOUT]->deBloquer();
		listeCamera[MODELEACCROUPI]->deBloquer();
		//gfx::Gestionnaire3D::obtInstance().obtCamera()->deBloquer();
	}

	gfx::Modele3D* obtModele3D() { return modele3D; }

	bool obtBloque(){ return bloque; }

	double obtAngleHorizontal(){ return camera->obtHAngle(); }

	Vecteur3d& obtNormale(){ return this->normale; }

	Vecteur3d obtPositionCamera(){
		//Vecteur3d temp = camera->obtPosition();
		//temp.y = temp.y - 1.8f;
		return camera->obtPosition();
	}

	void defSantePhysique(short santePhysique) { this->santePhysique = santePhysique; }

	void defSanteMentale(short santeMentale) { this->santeMentale = santeMentale; }

	short obtSantePhysique(){ return santePhysique; }

	short obtSanteMentale(){ return santeMentale; }

	Vecteur3d& obtPointCollision(){ return this->pointCollision; }

	Vecteur3d& obtPosition(){ return this->position; }

	Vecteur3d& obtVitesse(){ return this->vitesse; }

	double obtMasse(){ return masse; }

	float obtVitesseDeplacement(){ return vitesseDeplacement; }

	int obtEtat(){ return etat; }

	Vecteur3d obtVectOrientationVue() { return camera->obtDevant(); }
};
