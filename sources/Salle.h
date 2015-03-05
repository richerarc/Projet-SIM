#pragma once
#include "Vecteur3.h"
class Salle{
protected:
	unsigned int ID;
	Vecteur3d pos;
	Vecteur3d posEntreePortail;
public:
	Salle(unsigned int Id, Vecteur3d Pos, Vecteur3d PosEntreePortail){
		ID = Id;
		pos = Pos;
		posEntreePortail = PosEntreePortail;
	}

	unsigned int obtID(){
		return ID;
	}

	Vecteur3d obtPos(){
		return pos;
	}

	void modifPos(Vecteur3d Vecteur){
		pos = Vecteur;
	}

	Vecteur3d obtPosEntrePortail(){
		return posEntreePortail;
	}

	void modifPosEntrePortail(Vecteur3d Vecteur){
		posEntreePortail = Vecteur;
	}

	//Accesseurs de modele.
};