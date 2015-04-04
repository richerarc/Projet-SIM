#pragma once
#include "ObjetInventaire.h"

class Clef : public ObjetInventaire{
public:
	Clef(gfx::Modele3D modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool dansInventaire, unsigned int quantite) : ObjetInventaire(modele, ID, materiaux, masse, vitesse, position, vitesseAngulaire, false, false, dansInventaire, quantite){
	}
};