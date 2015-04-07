#pragma once
#include "ObjetInventaire.h"

class Couteau : public ObjetPhysique{
public:
	Couteau(gfx::Modele3D modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne, bool ramassable, unsigned int quantite, bool equipable, bool utilisable, bool dansInventaire) : ObjetPhysique(modele, ID, materiaux, masse, vitesse, position, vitesseAngulaire, collisionInterne, ramassable, quantite, equipable, utilisable, dansInventaire){
	}
};