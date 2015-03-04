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

	unsigned int obtenirID(){
		return ID;
	}

	Vecteur3 obtenirPos(){
		return pos;
	}

	void modifierPos(Vecteur3 Vecteur){
		pos = Vecteur;
	}

	Vecteur3 obtenirPosEntrePortail(){
		return posEntreePortail;
	}

	void modifierPosEntrePortail(Vecteur3 Vecteur){
		posEntreePortail = Vecteur;
	}

	//Accesseurs de modele.
};