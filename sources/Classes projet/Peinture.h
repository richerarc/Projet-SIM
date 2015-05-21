#pragma once
#include "Carte.h"
#include "ObjetFixe.h"

class Peinture : public ObjetFixe{
private:
	Vecteur3d normale;
public:
	Peinture(unsigned int ID, gfx::Modele3D* modele, Vecteur3d position, Vecteur3d normale) : ObjetFixe(modele, ID, "carton", position, Vecteur3d(), false, false){
		this->modele->defPosition(position + normale * 0.005);
		float echelleRand = (rand() % 100 + 100) / 100;
		this->modele->defEchelle(echelleRand, echelleRand, echelleRand);
		double vRot = Maths::radianADegre(normale.angleEntreVecteurs(Vecteur3d(this->modele->obtModele()->obtNormales()[0], this->modele->obtModele()->obtNormales()[1], this->modele->obtModele()->obtNormales()[2])));

		Vecteur3d normaleModele = Vecteur3d(1, 0, 0);
		this->modele->rotationner(normaleModele.produitVectoriel(normale), vRot);
		this->modele->rotationner(normaleModele, rand() % 360 - 180);
	}

};