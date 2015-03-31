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
	typeObjet type;
public:
	Objet(){}
	Objet(gfx::Modele3D& modele, unsigned int ID, char* materiaux,double masse,Vecteur3d vitesse, Vecteur3d position, typeObjet type){
		this->modele = modele;
		this->ID = ID;
		this->materiaux = materiaux;
		this->masse = masse;;
		this->vitesse.x = vitesse.x;
		this->vitesse.y = vitesse.y;
		this->vitesse.z = vitesse.z;
		this->modele.defPosition(position);
		this->type = type;
	}
	virtual void appliquerPhysique(std::list<Objet*> objets) = 0;
	virtual void appliquerAction(typeAction action) = 0;
	Vecteur3d obtPosition(){ 
		return this->modele.obtPosition(); 
	};
	void defPosition(Vecteur3d position){
		this->modele.defPosition(position);
	}
	
	void defID(unsigned int ID){
		this->ID = ID;
	}

	void defMateriaux(char* materiaux){
		this->materiaux = materiaux;
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
	
};
