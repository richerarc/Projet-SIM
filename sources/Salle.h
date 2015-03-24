#pragma once
#include "Vecteur3.h"
class Salle{
protected:
	unsigned int ID;
	unsigned int nbrPortes;
	Modele3D modele;
public:
	Salle(){}
	
	Salle(Modele3D modele,unsigned int nbrPorte, int ID){
		nbrPortes = nbrPorte;
		this->ID = ID;
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
		return modele->obtPosition();
	}

	void defPosition(int axeX, int axeY, int axeZ){
		modele->defPosition(axeX, axeY, axeZ);
	}

	Modele3D obtModele(){
		return modele;
	}
};