#pragma once
#include "Gestionnaire3D.h"
#include "Vecteur3.h"

enum etat { STABLE, ACCROUPI, COURSE, MARCHE, SAUT, CHUTE };
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
	}

	~Joueur() {
		delete listeCamera[0];
		delete listeCamera[1];
		delete listeModele3D[0];
		delete listeModele3D[1];
	}

	void deplacement(float frametime){
		if (!bloque){
			if ((Clavier::toucheRelachee(SDLK_w) || Clavier::toucheRelachee(SDLK_s) || Clavier::toucheRelachee(SDLK_a) || Clavier::toucheRelachee(SDLK_d)) && (etat == STABLE || etat == MARCHE || etat == ACCROUPI)){
				vitesse.x = 0;
				vitesse.z = 0;
				if (vitesse.y == 0){
					etat = STABLE;
					vitesse.y = 0.f;
					}
				etat = STABLE;
			}

			if (etat == CHUTE && vitesse.x == 0 && vitesse.y == 0 && vitesse.z == 0)
				etat = STABLE;

			Vecteur3d cote = camera->obtCote();
			Vecteur3d devant = camera->obtDevant();
			Vecteur3d vitesseTemp;
			devant.y = 0;
			cote.y = 0;

			if (Clavier::toucheRelachee(SDLK_LSHIFT) && vitesseDeplacement != 4.f && etat != ACCROUPI)
				vitesseDeplacement = 4.f;

			if (etat != SAUT && etat != CHUTE) {
				if (Clavier::toucheAppuyee(SDLK_LSHIFT) && etat != ACCROUPI && vitesseDeplacement != 8.f)
					vitesseDeplacement = 9.f;

				else if (Clavier::toucheAppuyee(SDLK_LCTRL) && (etat != ACCROUPI)) {
					camera = listeCamera[MODELEACCROUPI];
					modele3D = listeModele3D[MODELEACCROUPI];
					ajouterScene();
					etat = ACCROUPI;
					vitesseDeplacement = 2.f;
				}

				else if (Clavier::toucheRelachee(SDLK_LCTRL) && (etat == ACCROUPI || etat == STABLE || etat == MARCHE)) {
					camera = listeCamera[MODELEDEBOUT];
					modele3D = listeModele3D[MODELEDEBOUT];
					ajouterScene();
					etat = STABLE;
					vitesseDeplacement = 4.f;
				}

				if (Clavier::toucheAppuyee(SDLK_w)){
					etat = MARCHE;
					vitesse.x = devant.x * vitesseDeplacement;
					vitesse.z = devant.z * vitesseDeplacement;
					if (vitesseDeplacement < 5) {
						if (Clavier::toucheAppuyee(SDLK_d)) {
							vitesse.x = vitesse.x + (cote.x * vitesseDeplacement);
							vitesse.z = vitesse.z + (cote.z * vitesseDeplacement);
						}

						else if (Clavier::toucheAppuyee(SDLK_a)) {
							vitesseTemp.x = cote.x * vitesseDeplacement;
							vitesseTemp.z = cote.z * vitesseDeplacement;
							vitesseTemp.x = -vitesseTemp.x;
							vitesseTemp.z = -vitesseTemp.z;
							vitesse.x = vitesse.x + vitesseTemp.x;
							vitesse.z = vitesse.z + vitesseTemp.z;
						}
					}

				}

				else if (Clavier::toucheAppuyee(SDLK_s)) {
					etat = MARCHE;
					vitesse = devant * vitesseDeplacement;
					vitesse.inverser();
					if (vitesseDeplacement < 5) {
						if (Clavier::toucheAppuyee(SDLK_d))
							vitesse = vitesse + (cote * vitesseDeplacement);

						else if (Clavier::toucheAppuyee(SDLK_a)) {
							vitesseTemp = cote * vitesseDeplacement;
							vitesseTemp.inverser();
							vitesse = vitesse + vitesseTemp;
						}
					}
				}

				else if (Clavier::toucheAppuyee(SDLK_a)) {
					etat = MARCHE;
					vitesse = cote * vitesseDeplacement;
					vitesse.inverser();
				}

				else if (Clavier::toucheAppuyee(SDLK_d)){
					etat = MARCHE;
					vitesse = cote * vitesseDeplacement;
				}

				if (Clavier::toucheAppuyee(SDLK_SPACE) && etat != ACCROUPI) {
					vitesse.y = 5;
					etat = CHUTE;
				}
			}
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
		listeCamera[MODELEDEBOUT]->defPosition(Vecteur3d(position.x, position.y + 1.8f, position.z));
		listeCamera[MODELEACCROUPI]->defPosition(Vecteur3d(position.x, position.y + 1.2f, position.z));
	}

	void defPositionY(double y) {
		this->position.y = y;
		this->modele3D->defPosition(position);
		listeCamera[MODELEDEBOUT]->defPosition(Vecteur3d(position.x, position.y + 1.8f, position.z));
		listeCamera[MODELEACCROUPI]->defPosition(Vecteur3d(position.x, position.y + 1.2f, position.z));
	}

	void defPointCollision(Vecteur3d pointCollision){
		this->pointCollision = pointCollision;
	}

	void defNormale(Vecteur3d normale){ this->normale = normale; }

	void defAngleHorizontal(double hAngle){ camera->defHAngle(Maths::degreARadian(hAngle)); }

	void defEtat(unsigned int etat){ if (etat <= 5) this->etat = etat; }

	void bloquer(){
		this->bloque = true;
		gfx::Gestionnaire3D::obtInstance().obtCamera()->bloquer();
	}

	void deBloquer(){
		this->bloque = false;
		gfx::Gestionnaire3D::obtInstance().obtCamera()->deBloquer();
	}

	gfx::Modele3D* obtModele3D() { return modele3D; }

	bool obtBloque(){ return bloque; }

	double obtHAngle(){ return camera->obtHAngle(); }

	Vecteur3d& obtNormale(){ return this->normale; }

	Vecteur3d obtPositionCamera(){
		Vecteur3d temp = camera->obtPosition();
		temp.y = temp.y - 1.8f;
		return temp;
	}

	short obtSantePhysique(){ return santePhysique; }

	short obtSanteMentale(){ return santeMentale; }

	Vecteur3d& obtPointCollision(){ return this->pointCollision; }

	Vecteur3d& obtPosition(){ return this->position; }

	Vecteur3d& obtVitesse(){ return this->vitesse; }

	double obtMasse(){ return masse; }

	float obtVitesseDeplacement(){ return vitesseDeplacement; }

	int obtEtat(){ return etat; }


};
