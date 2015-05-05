#pragma once
#include <list>
#include "Gestionnaire3D.h"

class Objet {
protected:
	unsigned int ID;
	gfx::Modele3D* modele;
	char* materiaux;
	double masse;
	Vecteur3d vitesse;
	bool collisionInterne;
	Vecteur3d position;
	Vecteur3d vitesseAngulaire;
public:
	Objet(){}
	Objet(gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne){
		this->modele = modele;
		this->ID = ID;
		this->materiaux = materiaux;
		this->masse = masse;
		this->vitesse = vitesse;
		this->modele->defPosition(position);
		this->collisionInterne = collisionInterne;
		this->position = position;
		this->vitesseAngulaire = vitesseAngulaire;
	}

	~Objet() {
		gfx::Gestionnaire3D::obtInstance().retObjet(modele);
		//delete modele;
	}

	
	virtual bool obtSiPorte() = 0;
	//virtual void ajouterScene() = 0;

	void remplir() {
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(this->modele);
	}

	void defPosition(Vecteur3d position){
		if (modele->obtModele() != NULL){
			this->modele->defPosition(position);
		}
		this->position = position;
	}

	void defID(unsigned int ID){
		this->ID = ID;
	}

	void defMateriaux(char* materiaux){
		this->materiaux = materiaux;
	}

	void defVitesseAngulaire(Vecteur3d vitesseAngulaire){
		this->vitesseAngulaire = vitesseAngulaire;
	}

	void defCollisionInterne(bool collisionInterne){
		this->collisionInterne = collisionInterne;
	}

	void defMasse(double masse){
		this->masse = masse;
	}

	void defVitesse(Vecteur3d vitesse){
		this->vitesse = vitesse;
	}

	unsigned int obtID(){
		return this->ID;
	}

	gfx::Modele3D* obtModele3D(){
		return modele;
	}

	char* obtMateriaux(){
		return materiaux;
	}

	double obtMasse(){
		return masse;
	}

	Vecteur3d& obtVitesse(){
		return vitesse;
	}

	Vecteur3d& obtPosition(){
		if (modele->obtModele() != NULL)
			return this->modele->obtPosition();
		else
			return this->position;
	}

	bool obtCollisionInterne(){
		return collisionInterne;
	}

	Vecteur3d& obtVitesseAngulaire(){
		return vitesseAngulaire;
	}


};
