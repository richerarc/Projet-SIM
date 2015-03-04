#pragma once
#include "Vecteur3.h"
class Salle{
protected:
	unsigned int ID;
	Vecteur3<double> pos;
	Vecteur3<double> posEntreePortail;
	//Modele help wth dude
public:
	Salle(unsigned int Id, Vecteur3<double> Pos, Vecteur3<double> PosEntreePortail, /*modele*/){
		ID = Id;
		pos = Pos;
		posEntreePortail = PosEntreePortail;
		/*modele*/
	}

	unsigned int obtID(){
		return ID;
	}

	Vecteur3 obtPos(){
		return pos;
	}

	void modifPos(Vecteur3 Vecteur){
		pos = Vecteur;
	}

	Vecteur3 obtPosEntrePortail(){
		return posEntreePortail;
	}

	void modifPosEntrePortail(Vecteur3 Vecteur){
		posEntreePortail = Vecteur;
	}

	//Accesseurs de modele.
};