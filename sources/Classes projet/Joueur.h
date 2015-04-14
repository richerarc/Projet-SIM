#pragma once
#include "Gestionnaire3D.h"
#include "Vecteur3.h"

class Joueur {
private:
	gfx::Modele3D* modele3D;
	gfx::Camera* camera;
	Vecteur3d position;
	Vecteur3d vitesse;
	double masse;
	float vitesseDeplacement;
	bool accroupie;
	bool saut;

public:

	Joueur() {}

	Joueur(gfx::Modele3D* modele3D, Vecteur3d position) {
		this->modele3D = modele3D;
		this->vitesseDeplacement = 4.f;
		this->modele3D->defPosition(position);
		this->position = position;
		masse = 87.f;
		camera = new gfx::Camera();
		vitesse = { 0, 0.01, 0 };
		saut = true;
	}

	void deplacement(float frametime){

		if ((Clavier::toucheRelachee(SDLK_w) || Clavier::toucheRelachee(SDLK_s) || Clavier::toucheRelachee(SDLK_a) || Clavier::toucheRelachee(SDLK_d)) && vitesse.x != 0 && vitesse.z != 0 && !saut) {
			vitesse.x = 0;
			vitesse.z = 0;
			if (vitesse.y == 0)
				vitesse.y = 0.01;
		}

		Vecteur3d devant = camera->obtDevant();
		devant.y = 0;
		Vecteur3d cote = camera->obtCote();
		cote.y = 0;
		if (!saut) {
			if (Clavier::toucheAppuyee(SDLK_w))
				vitesse = devant * vitesseDeplacement;
			if (Clavier::toucheAppuyee(SDLK_s)) {
				vitesse = devant * vitesseDeplacement;
				vitesse.inverser();
			}
			if (Clavier::toucheAppuyee(SDLK_a)) {
				vitesse = cote * vitesseDeplacement;
				vitesse.inverser();
			}
			if (Clavier::toucheAppuyee(SDLK_d))
				vitesse = cote * vitesseDeplacement;
			if (Clavier::toucheAppuyee(SDLK_LCTRL)) {
				camera->defPosition(Vecteur3d(camera->obtPosition().x, camera->obtPosition().y - 0.80, camera->obtPosition().z));
				accroupie = true;
			}
		}
		if (Clavier::toucheRelachee(SDLK_LCTRL)) {
			camera->defPosition(Vecteur3d(camera->obtPosition().x, camera->obtPosition().y + 0.80, camera->obtPosition().z));
			accroupie = false;
		}
		if (Clavier::toucheAppuyee(SDLK_SPACE) && !saut) {
			vitesse.y = 6;
			saut = true;
		}

	}

	void ajouterScene(){
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele3D);
		gfx::Gestionnaire3D::obtInstance().defCamera(camera);
	}

	gfx::Modele3D* obtModele3D() {
		return modele3D;
	}

	void defPosition(Vecteur3d pos){
		this->position = pos;
		this->modele3D->defPosition(position);
		camera->defPosition(Vecteur3d(position.x ,position.y + 3.5, position.z));
	}

	void defSaut(bool saut) {
		this->saut = saut;
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
	
	bool enSaut() {
		return saut;
	}
};