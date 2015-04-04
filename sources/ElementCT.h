#pragma once
#include "ObjetInventaire.h"

//élément d'un casse-tête
class ElementCT : public ObjetInventaire{
public:
	ElementCT(gfx::Modele3D modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire,bool equipable, bool utilisable, bool dansInventaire, unsigned int quantite) : ObjetInventaire(modele, ID, materiaux, masse, vitesse, position, vitesseAngulaire, equipable, utilisable, dansInventaire, quantite){
	}
};