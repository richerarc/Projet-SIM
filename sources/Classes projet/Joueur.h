#pragma once
#include "Gestionnaire3D.h"
#include "Vecteur3.h"
#include "Plan.h"
#include "Inventaire.h"
#include "Physique.h"
#include "GestionnaireControle.h"

enum etatDynamique { STABLE, MARCHE, SAUT, CHUTE };
enum etatStatique { DEBOUT, ACCROUPI };

class Joueur {
private:
	gfx::Modele3D* modele3D;
	gfx::Camera* camera;
	gfx::Modele3D* listeModele3D[2];
	Vecteur3d position;
	Vecteur3d vitesse;
	Vecteur3d normale;
	Vecteur3d pointCollision;
	Vecteur3d verticesCollision[3];
	double masse;
	float vitesseDeplacement;
	short santePhysique, santeMentale;
	short etatDynamique;
	float etatStatique;
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
		}
	}

public:

	Joueur() {}

	Joueur(Vecteur3d position, double hAngle) {
		this->vitesseDeplacement = 4.f;
		this->position = position;
		etatDynamique = CHUTE;
		masse = 87.f;
		santePhysique = 100;
		santeMentale = 100;
		vitesse = { 0, 0, 0 };
		bloque = false;
		listeModele3D[DEBOUT] = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Joueur.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));
		listeModele3D[ACCROUPI] = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("JoueurAccroupi.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));
		listeModele3D[DEBOUT]->defPosition(position);
		listeModele3D[ACCROUPI]->defPosition(position);
		camera = new gfx::Camera();
		position.y += 1.74;
		camera->defPosition(position);
		etatStatique = DEBOUT;
		modele3D = listeModele3D[DEBOUT];
		camera->defHAngle(hAngle);
		chronoSaut = Chrono();
		inventaire = new Inventaire(Vecteur2f(9, 3));
	}

	~Joueur() {
		delete camera;
		delete listeModele3D[0];
		delete listeModele3D[1];
		delete inventaire;
	}

	void deplacement(float frameTime){
		if (!bloque){
			if ((Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(AVANCER)) || Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(RECULER)) || Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(GAUCHE)) || Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(DROITE))) && (etatDynamique == MARCHE)){
				vitesse.x = 0.f;
				vitesse.z = 0.f;
				if (vitesse.y == 0){
					etatDynamique = STABLE;
					vitesse.y = 0.f;
				}
				etatDynamique = STABLE;
			}

			if (etatDynamique == CHUTE && vitesse.x == 0 && vitesse.y == 0 && vitesse.z == 0){
				etatDynamique = STABLE;
			}


			Vecteur3d devant = camera->obtDevant();
			Vecteur3d cote = camera->obtCote();
			Vecteur3d vitesseTemp;
			devant.y = 0;
			devant.normaliser();
			cote.y = 0;

			if (Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(COURIR)) && (vitesseDeplacement != 4.f) && (etatStatique == DEBOUT))
				vitesseDeplacement = 4.f;

			if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(ACCROUPIR)) && (etatStatique == DEBOUT)) {
				etatStatique = ACCROUPI;
				modele3D = listeModele3D[ACCROUPI];
				ajouterScene();
				vitesseDeplacement = 2.f;
			}

			else if (Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(ACCROUPIR)) && etatStatique == ACCROUPI) {
				etatStatique = DEBOUT;
				modele3D = listeModele3D[DEBOUT];
				ajouterScene();
				vitesseDeplacement = 4.f;
			}
			if (etatDynamique != CHUTE) {
				if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(COURIR)) && (etatStatique == DEBOUT) && vitesseDeplacement != 8.f)
					vitesseDeplacement = 8.f;



				/*if ((normale.x != 0 || normale.z != 0) && (normale.y != 0)) {
				vitesseDeplacement = 4.f;
				}*/

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
					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						if (devant.produitScalaire(tmpNormale) > 0.f) {
							etatDynamique = MARCHE;
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(RECULER))) {
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
					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						//ajusterVitesse();
						//vitesse *= 2;
						if (vitesse.produitScalaire(tmpNormale) > 0.f) {
							etatDynamique = MARCHE;
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
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

					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						if (vitesse.produitScalaire(tmpNormale) > 0.f) {
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(DROITE))){
					if (normale.x != 0.f || normale.z != 0.f) {
						vitesse.x = vitesse.x + (cote.x * vitesseDeplacement);
						vitesse.x = vitesse.x + (cote.x * vitesseDeplacement);
					}
					else
						vitesse = vitesse + (cote * vitesseDeplacement);
					if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f)) || normale == Vecteur3d(0, 0, 0)) {
						Vecteur3d tmpNormale;
						if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
							tmpNormale = normale;
						}
						if (vitesse.produitScalaire(tmpNormale) > 0.f) {
							ajusterVitesse();
							if (vitesse.y > 0.f) {
								vitesse.y *= -1;
							}
						}
					}
				}

				if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(SAUTER)) && (etatStatique == DEBOUT)) {
					if ((chronoSaut.obtTempsEcoule().enSecondes() > 1.15))
					{
						chronoSaut.repartir();
						vitesse.y = 7;
						etatDynamique = CHUTE;
					}
				}
			}
			//	short typeCollision = Physique::obtInstance().collisionJoueurSalle(modele3D, modele3D->obtBoiteDeCollisionModifiee(), vitesse, normale, pointCollision, position);
			if (normale.x == 0.f && normale.z == 0.f && normale.y != 0)
				modele3D->defOrientation(0, (camera->obtHAngle()), 0);
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
		this->modele3D->defPosition(position);
		if (etatStatique)
			camera->defPosition(Vecteur3d(position.x, position.y + 1.00f, position.z));
		else
			camera->defPosition(Vecteur3d(position.x, position.y + 1.74f, position.z));
		/*listeCamera[DEBOUT]->defPosition(Vecteur3d(position.x, position.y + 1.74f, position.z));
		listeCamera[ACCROUPI]->defPosition(Vecteur3d(position.x, position.y + 1.00f, position.z));*/
	}

	void defPositionY(double y) {
		this->position.y = y;
		this->modele3D->defPosition(position);
		if (etatStatique)
			camera->defPosition(Vecteur3d(position.x, position.y + 1.00f, position.z));
		else
			camera->defPosition(Vecteur3d(position.x, position.y + 1.74f, position.z));
	}

	void defPointCollision(Vecteur3d pointCollision){
		this->pointCollision = pointCollision;
	}

	void defNormale(Vecteur3d normale){ this->normale = normale; }
	void defNormaleMur(Vecteur3d normaleMur){ this->normaleMur = normaleMur; }

	void defAngleHorizontal(double hAngle){
		/*listeCamera[DEBOUT]->defHAngle(Maths::degreARadian(hAngle));
		listeCamera[ACCROUPI]->defHAngle(Maths::degreARadian(hAngle));*/
		camera->defHAngle(Maths::degreARadian(hAngle));
	}

	gfx::Camera* obtCamera(){ return camera; }

	void defEtat(unsigned int etatDynamique){ if (etatDynamique <= 4) this->etatDynamique = etatDynamique; }

	void bloquer(){
		this->bloque = true;
		/*listeCamera[DEBOUT]->bloquer();
		listeCamera[ACCROUPI]->bloquer();*/
		//gfx::Gestionnaire3D::obtInstance().obtCamera()->bloquer();
		camera->bloquer();
	}

	void deBloquer(){
		this->bloque = false;
		/*listeCamera[DEBOUT]->deBloquer();
		listeCamera[ACCROUPI]->deBloquer();*/
		//gfx::Gestionnaire3D::obtInstance().obtCamera()->deBloquer();
		camera->deBloquer();
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

	Vecteur3d* obtVerticesCollision(){ return this->verticesCollision; }

	Vecteur3d& obtPosition(){ return this->position; }

	Vecteur3d& obtVitesse(){ return this->vitesse; }

	double obtMasse(){ return masse; }

	float obtVitesseDeplacement(){ return vitesseDeplacement; }

	int obtEtat(){ return etatDynamique; }

	Vecteur3d obtVectOrientationVue() { return camera->obtDevant(); }

	Inventaire* obtInventaire(){ return this->inventaire; }
};
