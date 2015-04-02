#pragma once
#include "ObjetInventaire.h"

class Fusil : public ObjetInventaire{
public:
	Fusil(gfx::Modele3D modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool dansInventaire, unsigned int quantite) : ObjetInventaire(modele,ID,materiaux,masse,vitesse,position,vitesseAngulaire,true,false,dansInventaire,quantite){
	}
};