#include "Vecteur3.h"

class Salle{
protected:
	unsigned int ID;
	Vecteur3<double> Pos;
	Vecteur3<double> PosEntreePortail;
	//Modele help wth dude
public:
	Salle(){

	}

	unsigned int ObtenirID(){
		return ID;
	}

	Vecteur3 ObtenirPos(){
		return Pos;
	}

	void ModifierPos(Vecteur3 Vecteur){
		Pos = Vecteur;
	}

	Vecteur3 ObtenirPosEntrePortail(){
		return Pos;
	}

	void ModifierPosEntrePortail(Vecteur3 Vecteur){
		Pos = Vecteur;
	}

	//Accesseurs de modele.
};