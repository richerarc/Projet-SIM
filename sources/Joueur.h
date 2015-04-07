#pragma once
#include "Gestionnaire3D.h"
#include "Vecteur3.h"
#include "Objet.h"
#include "Piece.h"

class Joueur : public Objet{
private:
	gfx::Modele3D modele3D;
	gfx::Camera camera;

	float vitesseDeplacement;
	bool accroupie;

public:
	Joueur(gfx::Modele3D &modele3D, unsigned int ID, double masse, Vecteur3d position) : Objet(modele3D, ID, NULL, masse, NULL, position, NULL ,false){
		this->modele3D = modele3D;
		this->vitesseDeplacement = 0.2;
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
		camera.defPosition(position);
	}

	void appliquerPhysique(Piece &piece, double frametime) {
		if (!Physique::obtInstance().collisionJoueurSalle(*this, piece)) {
			Physique::obtInstance().appliquerGravite(vitesse, frametime);
		}
		defPosition(position + (vitesse * frametime));
	}

	void ajouterScene(){
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(&modele3D);
		gfx::Gestionnaire3D::obtInstance().defCamera(&camera);
	}

	gfx::Modele3D& obtModele3D() {
		return modele3D;
	}
};