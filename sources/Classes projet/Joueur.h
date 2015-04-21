#pragma once
#include "Gestionnaire3D.h"
#include "Vecteur3.h"

enum etat {STABLE, ACCROUPI, COURSE, MARCHE, SAUT, CHUTE};

class Joueur {
private:
	gfx::Modele3D* modele3D;
	gfx::Camera* camera;
	std::list<Objet*> inventaire;
	Vecteur3d position;
	Vecteur3d vitesse;
	double masse;
	float vitesseDeplacement;
	short santePhysique,
		  santeMentale;
	int etat;
	Vecteur3d pointCollision;

public:

	Joueur() {}

	Joueur(gfx::Modele3D* modele3D, Vecteur3d position) {
		this->modele3D = modele3D;
		this->vitesseDeplacement = 4.f;
		this->modele3D->defPosition(position);
		this->position = position;
		santePhysique = 100;
		santeMentale = 75;
		etat = CHUTE;
		masse = 87.f;
		camera = new gfx::Camera();
		vitesse = { 0, -0.01, 0 };
	}

	void deplacement(float frametime){

		//if ((Clavier::toucheRelachee(SDLK_w) || Clavier::toucheRelachee(SDLK_s) || Clavier::toucheRelachee(SDLK_a) || Clavier::toucheRelachee(SDLK_d)) && vitesse.x != 0 && vitesse.z != 0 && (etat != SAUT) && (etat != CHUTE)){
		if ((Clavier::toucheRelachee(SDLK_w) || Clavier::toucheRelachee(SDLK_s) || Clavier::toucheRelachee(SDLK_a) || Clavier::toucheRelachee(SDLK_d)) && (etat == STABLE || etat == MARCHE)){
 			vitesse.x = 0;
			vitesse.z = 0;
			//if (etat = CHUTE)
				//etat = STABLE;
			if (vitesse.y == 0){
				etat = STABLE;
				vitesse.y = 0.01;
			}
		}
		if (etat == CHUTE && vitesse.x == 0 && vitesse.y == 0){
			etat = STABLE;
		}
		Vecteur3d devant = camera->obtDevant();
		devant.y = 0;
		Vecteur3d cote = camera->obtCote();
		cote.y = 0;
		if (etat != SAUT && etat != CHUTE) {
			if (Clavier::toucheAppuyee(SDLK_w)){
				etat = MARCHE;
				vitesse = devant * vitesseDeplacement;
			}
			if (Clavier::toucheAppuyee(SDLK_s)) {
				etat = MARCHE;
				vitesse = devant * vitesseDeplacement;
				vitesse.inverser();
			}
			if (Clavier::toucheAppuyee(SDLK_a)) {
				etat = MARCHE;
				vitesse = cote * vitesseDeplacement;
				vitesse.inverser();
			}
			if (Clavier::toucheAppuyee(SDLK_d)){
				etat = MARCHE;
				vitesse = cote * vitesseDeplacement;
			}
			if (Clavier::toucheAppuyee(SDLK_LCTRL) && (etat != ACCROUPI)) {
				camera->defPosition(Vecteur3d(camera->obtPosition().x, camera->obtPosition().y - 3.80, camera->obtPosition().z));
				etat = ACCROUPI;
			}
		}
		if (Clavier::toucheRelachee(SDLK_LCTRL) && (etat == ACCROUPI)) {
			camera->defPosition(Vecteur3d(camera->obtPosition().x, camera->obtPosition().y + 0.80, camera->obtPosition().z));
			etat = STABLE;
		}
		if (Clavier::toucheAppuyee(SDLK_SPACE) && (etat != SAUT) && etat != CHUTE) {
			vitesse.y = 5;
			etat = SAUT;
		}

	}

	void ajouterScene(){
		gfx::Gestionnaire3D::obtInstance().defCamera(camera);
	}

	gfx::Modele3D* obtModele3D() {
		return modele3D;
	}

	void defPosition(Vecteur3d pos){
		this->position = pos;
		this->modele3D->defPosition(position);
		camera->defPosition(Vecteur3d(position.x ,position.y + 1.80, position.z));
	}
	void defPointCollision(Vecteur3d pointCollision){
		this->pointCollision = pointCollision;
	}

	void defSanteMentale(float santeMentale){
		this->santeMentale = santeMentale;
	}

	void defSantePhysique(float santePhysique){
		this->santeMentale = santePhysique;
	}

	Vecteur3d& obtPointCollision(){
		return this->pointCollision;
	}

	Vecteur3d& obtPosition(){
		return this->position;
	}

	Vecteur3d& obtVitesse(){
		return this->vitesse;
	}
	double obtMasse(){
		return masse;
	}
	float obtVitesseDeplacement(){
		return vitesseDeplacement;
	}
	
	int obtEtat(){
		return etat;
	}

	short obtSantePhysique(){
		return santePhysique;
	}

	short obtSanteMentale(){
		return santeMentale;
	}

	std::list<Objet*> obtInventaire(){
		return inventaire;
	}

	void defEtat(unsigned int etat){
		if (etat <= 5){
			this->etat = etat;
		}
	}
};