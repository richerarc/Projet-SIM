#pragma once
#include "ObjetFixe.h"

class Balance : public ObjetFixe{
private:
	double distanceSeau;
	double poidGauche;
	double poidDroite;

public:
	Balance(gfx::Modele3D* modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool interactif, double distanceSeau) : ObjetFixe(modele, ID, materiaux, position, vitesseAngulaire, collisionInterne, interactif){
		this->distanceSeau = distanceSeau;

		poidGauche = 0;
		poidDroite = 0;
		calculerAnlge();
	}

	double obtDistance(){
		//Fill in later.
	}

	void ajouterPoidGauche(double poid) {
		poidGauche += poid;
	}

	void ajouterPoidDroite(double poid) {
		poidDroite += poid;
	}

	void calculerAnlge() {

		double pourquoiPas = poidGauche - poidDroite;

		if (pourquoiPas > 25)
			pourquoiPas = 25;
		if (pourquoiPas < -25)
			pourquoiPas = -25;
		modele->defOrientation({ 0, 0, pourquoiPas});
		
	}

};