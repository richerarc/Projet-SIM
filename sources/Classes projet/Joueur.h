#pragma once
#include "Gestionnaire3D.h"
#include "Vecteur3.h"

class Joueur {
private:
	gfx::Modele3D* modele3D;
	gfx::Camera camera;
	Vecteur3d position;
	Vecteur3d vitesse;
	float vitesseDeplacement;
	bool accroupie;

public:

	Joueur() {}

	Joueur(gfx::Modele3D* modele3D, unsigned int ID, double masse, Vecteur3d position) {
		this->modele3D = modele3D;
		this->vitesseDeplacement = 0.2f;
		this->position = position;
	}

	void deplacement(float frametime){
		Vecteur3d devant = camera.obtDevant();
		Vecteur3d cote = camera.obtDevant();
		if (Clavier::toucheAppuyee(SDLK_w))
			position += devant * vitesseDeplacement * frametime;
		if (Clavier::toucheAppuyee(SDLK_s))
			position -= devant * vitesseDeplacement * frametime;
		if (Clavier::toucheAppuyee(SDLK_a))
			position -= cote * vitesseDeplacement * frametime;
		if (Clavier::toucheAppuyee(SDLK_d))
			position += cote * vitesseDeplacement * frametime;
		if (Clavier::toucheAppuyee(SDLK_LSHIFT)) {
			camera.defPosition(Vecteur3d(camera.obtPosition().x, camera.obtPosition().y - 0.80, camera.obtPosition().z));
			accroupie = true;
		}
		if (Clavier::toucheRelachee(SDLK_LSHIFT)) {
			camera.defPosition(Vecteur3d(camera.obtPosition().x, camera.obtPosition().y + 0.80, camera.obtPosition().z));
			accroupie = false;
		}
		camera.defPosition(position);
	}

	void ajouterScene(){
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele3D);
		gfx::Gestionnaire3D::obtInstance().defCamera(&camera);
	}

	gfx::Modele3D* obtModele3D() {
		return modele3D;
	}

	void defPosition(Vecteur3d pos){
		this->position = pos;
	}

	Vecteur3d& obtPosition(){
		return this->position;
	}

	Vecteur3d& obtVitesse(){
		return this->vitesse;
	}
};