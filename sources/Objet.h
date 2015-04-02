#pragma once
/*
#include "ObjetPhysique.h"
#include "Vent.h"
#include "Aimant.h"
#include "Porte.h"
#include "Obstacle.h"
#include "Connecteur.h"
*/
//Objet
//-ObjetFixe
//---Pendule
//---Balance
//---Inactif
//-ObjetInteractif
//--Projectile
//--ObjInv
//---Fusil
//---Couteau
//---Clé
//---Fil
//---Balle
//---AlimentPhysique
//---AlimentMental
//---Autre
//
//-Force
//
//

enum typeAction {Rotation, Pousser, Osciller, Prendre, Ranger, Tirer, Recharger, Lancer, Utiliser};
enum typeObjet {Pendule,Balance,Inactif,Projectile,Fusil,Couteau,Clef,Fil,Balle,AlimentPhysique,AlimentMental,Autre,Vent,Aimant};

class Objet {
protected:
	unsigned int ID;
	gfx::Modele3D modele;
	char* materiaux;
	double masse;
	Vecteur3d vitesse;
	bool collisionInterne;
	Vecteur3d position;
	Vecteur3d vitesseAngulaire;
public:
	Objet(){}
	Objet(gfx::Modele3D& modele, unsigned int ID, char* materiaux,double masse,Vecteur3d vitesse, Vecteur3d position,Vecteur3d vitesseAngulaire,bool collisionInterne){
		this->modele = modele;
		this->ID = ID;
		this->materiaux = materiaux;
		this->masse = masse;;
		this->vitesse.x = vitesse.x;
		this->vitesse.y = vitesse.y;
		this->vitesse.z = vitesse.z;
		this->modele.defPosition(position);
		this->collisionInterne = collisionInterne;
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
		this->vitesseAngulaire.x = vitesseAngulaire.x;
		this->vitesseAngulaire.y = vitesseAngulaire.y;
		this->vitesseAngulaire.z = vitesseAngulaire.z;
	}
	virtual void appliquerPhysique(std::list<Objet*> objets) = 0;
	virtual void appliquerAction(typeAction action) = 0;
	
	void defPosition(Vecteur3d position){
		if (modele.obtModele() != NULL){
			this->modele.defPosition(position);
		}
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}
	
	void defID(unsigned int ID){
		this->ID = ID;
	}

	void defMateriaux(char* materiaux){
		this->materiaux = materiaux;
	}

	void defVitesseAngulaire(Vecteur3d vitesseAngulaire){
		this->vitesseAngulaire.x = vitesseAngulaire.x;
		this->vitesseAngulaire.y = vitesseAngulaire.y;
		this->vitesseAngulaire.z = vitesseAngulaire.z;
	}

	void defCollisionInterne(bool collisionInterne){
		this->collisionInterne = collisionInterne;
	}

	void defMasse(double masse){
		this->masse = masse;
	}

	void defVitesse(Vecteur3d vitesse){
		this->vitesse.x = vitesse.x;
		this->vitesse.y = vitesse.y;
		this->vitesse.z = vitesse.z;
	}
	
	unsigned int obtID(){
		return this->ID;
	}
	
	gfx::Modele3D& obtModele3D(){
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
		if (modele.obtModele() != NULL)
			return this->modele.obtPosition();
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
