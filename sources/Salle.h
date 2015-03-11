#pragma once
#include "Vecteur3.h"
class Salle{
protected:
	unsigned int ID;
	unsigned int nbrPortes;
	Vecteur3d pos;
	Modele3D modele;
public:
	Salle(){}
	
	Salle(Vecteur3d Pos, Modele3D modele,unsigned int nbrPorte){
		nbrPortes = nbrPorte;
		pos = Pos;
		this->modele = modele;
	}

	unsigned int obtNbrPortes(){
		return nbrPortes;
	}

	unsigned int obtID(){
		return ID;
	}
	
	void setID(unsigned int ID){
		this->ID = ID;
	}

	Vecteur3d obtPos(){
		return pos;
	}

	void modifPos(Vecteur3d Vecteur){
		pos = Vecteur;
	}

	Modele3D obtModele(){
		return modele;
	}
};