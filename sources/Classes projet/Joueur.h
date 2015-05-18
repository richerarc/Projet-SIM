#pragma once
#include "Gestionnaire3D.h"
#include "Vecteur3.h"
#include "Plan.h"
#include "GestionnaireControle.h"
#include "Inventaire.h"

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
	short etat;
	short santePhysique, santeMentale;
	Vecteur3d normale;
	Vecteur3d pointCollision;
	bool bloque;
	Chrono chronoSaut;
	Inventaire* inventaire;
	Vecteur3d normaleMur;

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
			Vecteur3d vitesseTemp = vitesse;
			vitesseTemp.normaliser();
			vitesseTemp *= vitesseDeplacement;
			vitesse.y = vitesseTemp.y;
		}
	}

public:

	Joueur() {}

	Joueur(Vecteur3d position, double hAngle) {
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
		listeModele3D[MODELEDEBOUT] = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/Joueur.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/Joueur.png"));
		listeModele3D[MODELEACCROUPI] = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/JoueurAccroupi.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/Joueur.png"));
		camera = listeCamera[MODELEDEBOUT];
		modele3D = listeModele3D[MODELEDEBOUT];
		listeModele3D[MODELEDEBOUT]->defPosition(position);
		listeModele3D[MODELEACCROUPI]->defPosition(position);
		chronoSaut = Chrono();
		position.y += 1.74;
		camera->defPosition(position);
		etat = STABLE;
		modele3D = listeModele3D[MODELEDEBOUT];
		camera->defHAngle(hAngle);
		chronoSaut = Chrono();
		inventaire = new Inventaire(Vecteur2f(9, 3));
	}

	~Joueur() {
		delete listeCamera[0];
		delete listeCamera[1];
		delete listeModele3D[0];
		delete listeModele3D[1];
		delete inventaire;
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
					if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(AVANCER)))
						vitesseDeplacement = 10.f;
					else
						vitesseDeplacement = 4.f;

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(ACCROUPIR)) && (camera != listeCamera[MODELEACCROUPI])) {
					listeCamera[MODELEACCROUPI]->defHAngle(listeCamera[MODELEDEBOUT]->obtHAngle());
					camera = listeCamera[MODELEACCROUPI];
					modele3D = listeModele3D[MODELEACCROUPI];
					ajouterScene();
					vitesseDeplacement = 2.f;
				}

				else if (Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(ACCROUPIR)) && camera != listeCamera[MODELEDEBOUT]) {
					listeCamera[MODELEACCROUPI]->defHAngle(listeCamera[MODELEDEBOUT]->obtHAngle());
					camera = listeCamera[MODELEDEBOUT];
					modele3D = listeModele3D[MODELEDEBOUT];
					ajouterScene();
					etat = STABLE;
					vitesseDeplacement = 4.f;
				}

				if (fabs(normale.x) < 0.05f)
					normale.x = 0.f;
				if (fabs(normale.z) < 0.05f)
					normale.z = 0.f;
				normale.normaliser();

				if ((normale.x != 0 || normale.z != 0) && (normale.y != 0)) {
					vitesseDeplacement = 4.f;
				}

				if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(AVANCER))) {
					if ((normale.x != 0.f || normale.z != 0.f) || normale == Vecteur3d(0, 0, 0)) {
						vitesse.x = devant.x * vitesseDeplacement;
						vitesse.z = devant.z * vitesseDeplacement;
					}
					else if (normale.x == 0.f && normale.z == 0.f && normale.y != 0.f)
						vitesse = devant * vitesseDeplacement;
					if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(DROITE))) {
						if (normale.x != 0.f || normale.z != 0.f) {
							vitesse.x = vitesse.x + (cote.x * vitesseDeplacement);
							vitesse.z = vitesse.z + (cote.z * vitesseDeplacement);
						}
						else
							vitesse = vitesse + (cote * vitesseDeplacement);
						vitesse.normaliser();
						vitesse *= vitesseDeplacement;
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
						vitesse.normaliser();
						vitesse *= vitesseDeplacement;
					}
					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						if (devant.produitScalaire(tmpNormale) > 0.f) {
							etat = MARCHE;
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(RECULER))) {
					vitesseDeplacement = 4.f;
					if ((normale.x != 0.f || normale.z != 0.f) || normale == Vecteur3d(0, 0, 0)) {
						vitesse.x = devant.x * vitesseDeplacement;
						vitesse.z = devant.z * vitesseDeplacement;
						vitesse.x = -vitesse.x;
						vitesse.z = -vitesse.z;
					}
					else if (normale.x == 0.f && normale.z == 0.f && normale.y != 0.f) {
						vitesse = devant * vitesseDeplacement;
						vitesse.inverser();
					}
					if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(DROITE))) {
						if (normale.x != 0.f || normale.z != 0.f) {
							vitesse.x = vitesse.x + (cote.x * vitesseDeplacement);
							vitesse.z = vitesse.z + (cote.z * vitesseDeplacement);
						}
						else
							vitesse = vitesse + (cote * vitesseDeplacement);
						vitesse.normaliser();
						vitesse *= vitesseDeplacement;
					}

					else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(GAUCHE))) {
						if (normale.x != 0.f || normale.z != 0.f) {
							vitesseTemp.x = cote.x * vitesseDeplacement;
							vitesseTemp.z = cote.z * vitesseDeplacement;
							vitesseTemp.x = -vitesseTemp.x;
							vitesseTemp.z = -vitesseTemp.z;
						}
						else {
							vitesseTemp = cote * vitesseDeplacement;
							vitesseTemp.inverser();
						}
						vitesse = vitesse + vitesseTemp;
						vitesse.normaliser();
						vitesse *= vitesseDeplacement;
					}
					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						//ajusterVitesse();
						//vitesse *= 2;
						if (vitesse.produitScalaire(tmpNormale) > 0.f) {
							etat = MARCHE;
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(GAUCHE))) {
					vitesseDeplacement = 4.f;
					if (normale.x != 0.f || normale.z != 0.f) {
						vitesseTemp.x = cote.x * vitesseDeplacement;
						vitesseTemp.z = cote.z * vitesseDeplacement;
						vitesseTemp.x = -vitesseTemp.x;
						vitesseTemp.z = -vitesseTemp.z;
					}
					else {
						vitesseTemp = cote * vitesseDeplacement;
						vitesseTemp.inverser();
					}
					vitesse = vitesse + vitesseTemp;

					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						if (vitesse.produitScalaire(tmpNormale) > 0.f) {
							etat = MARCHE;
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(DROITE))){
					vitesseDeplacement = 4.f;
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
						if (vitesse.produitScalaire(tmpNormale) > 0.f) {
							etat = MARCHE;
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
			if (normale.x == 0.f && normale.z == 0.f && normale.y != 0) {
				listeModele3D[MODELEDEBOUT]->defOrientation(0, (camera->obtHAngle()), 0);
				listeModele3D[MODELEACCROUPI]->defOrientation(0, (camera->obtHAngle()), 0);
			}
		}
	}


	void longer(){
		Vecteur3d direction1;
		Vecteur3d direction2;
		Vecteur3d vitesseNormalisee;
		direction1.x = -normaleMur.z;
		direction1.y = 0.f;
		direction1.z = normaleMur.x;
		direction2.x = normaleMur.z;
		direction2.y = 0.f;
		direction2.z = -normaleMur.x;
		vitesseNormalisee = vitesse;
		vitesseNormalisee.y = 0;
		vitesseNormalisee.normaliser();
		bool droit = false;
		if (normaleMur.x == 0. || normaleMur.z == 0.){
			droit = true;
			if (normaleMur.x == 0.){
				if (normaleMur.z == 1.){
					if (vitesse.x > 0.){
						vitesse.x = direction2.x * vitesseDeplacement;
						vitesse.z = direction2.z * vitesseDeplacement;
					}
					else{
						vitesse.x = direction1.x * vitesseDeplacement;
						vitesse.z = direction1.z * vitesseDeplacement;
					}
				}
				else{
					if (vitesse.x > 0.){
						vitesse.x = direction1.x * vitesseDeplacement;
						vitesse.z = direction1.z * vitesseDeplacement;
					}
					else{
						vitesse.x = direction2.x * vitesseDeplacement;
						vitesse.z = direction2.z * vitesseDeplacement;
					}
				}
			}
			if (normaleMur.z == 0.){
				if (normaleMur.x == 1.){
					if (vitesse.z > 0.){
						vitesse.x = direction1.x * vitesseDeplacement;
						vitesse.z = direction1.z * vitesseDeplacement;
					}
					else{
						vitesse.x = direction2.x * vitesseDeplacement;
						vitesse.z = direction2.z * vitesseDeplacement;
					}
				}
				else{
					if (vitesse.z > 0.){
						vitesse.x = direction2.x * vitesseDeplacement;
						vitesse.z = direction2.z * vitesseDeplacement;
					}
					else{
						vitesse.x = direction1.x * vitesseDeplacement;
						vitesse.z = direction1.z * vitesseDeplacement;
					}
				}
			}
		}
		if (!((vitesseNormalisee.x == direction1.x && vitesseNormalisee.z == direction1.z) || (vitesseNormalisee.x == direction2.x && vitesseNormalisee.z == direction2.z)) && !droit){

			if ((normaleMur.x <= 0. && normaleMur.z >= 0. && vitesseNormalisee.x > direction2.x && vitesseNormalisee.z < direction2.z) ||
				(normaleMur.x >= 0. && normaleMur.z >= 0. && vitesseNormalisee.x < direction2.x && vitesseNormalisee.z < direction2.z) ||
				(normaleMur.x <= 0. && normaleMur.z <= 0. && vitesseNormalisee.x > direction2.x && vitesseNormalisee.z > direction2.z) ||
				(normaleMur.x >= 0. && normaleMur.z <= 0. && vitesseNormalisee.x < direction2.x && vitesseNormalisee.z > direction2.z)
				){
				vitesse.x = direction2.x * vitesseDeplacement;
				vitesse.z = direction2.z * vitesseDeplacement;
			}
			else {
				if ((normaleMur.x <= 0. && normaleMur.z >= 0. && vitesseNormalisee.x >= direction1.x && vitesseNormalisee.z <= direction1.z) ||
					(normaleMur.x >= 0. && normaleMur.z >= 0. && vitesseNormalisee.x <= direction1.x && vitesseNormalisee.z <= direction1.z) ||
					(normaleMur.x <= 0. && normaleMur.z <= 0. && vitesseNormalisee.x >= direction1.x && vitesseNormalisee.z >= direction1.z) ||
					(normaleMur.x >= 0. && normaleMur.z <= 0. && vitesseNormalisee.x <= direction1.x && vitesseNormalisee.z >= direction1.z)
					){
					vitesse.x = direction1.x * vitesseDeplacement;
					vitesse.z = direction1.z * vitesseDeplacement;
				}
				else{
					vitesse.x = direction2.x * vitesseDeplacement;
					vitesse.z = direction2.z * vitesseDeplacement;
				}
			}
		}
	}

	void ajouterScene(){ gfx::Gestionnaire3D::obtInstance().defCamera(camera); }

	void defVitesseY(double y){ this->vitesse.y = y; }

	void defVitesse(Vecteur3d vitesse) { this->vitesse = vitesse; }

	void defPosition(Vecteur3d pos){
		this->position = pos;
		this->listeModele3D[MODELEACCROUPI]->defPosition(position);
		this->listeModele3D[MODELEDEBOUT]->defPosition(position);
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
	void defNormaleMur(Vecteur3d normaleMur){ this->normaleMur = normaleMur; }

	void defHAngle(double hAngle){
		listeCamera[MODELEDEBOUT]->defHAngle(hAngle);
		listeCamera[MODELEACCROUPI]->defHAngle(hAngle);
	}

	void defVAngle(double vAngle) {
		listeCamera[MODELEDEBOUT]->defVAngle(vAngle);
		listeCamera[MODELEACCROUPI]->defVAngle(vAngle);
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
	Vecteur3d& obtNormaleMur(){ return this->normaleMur; }

	Vecteur3d obtPositionCamera(){
		Vecteur3d temp = camera->obtPosition();
		temp.y = temp.y - 1.8f;
		return temp;
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

	short obtEtat(){ return etat; }

	Vecteur3d obtVectOrientationVue() { return camera->obtDevant(); }

	Inventaire* obtInventaire(){ return this->inventaire; }
};
