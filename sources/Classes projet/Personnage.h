#pragma once
#include "Carte.h"
#include "ObjetFixe.h"
#include "GestionnaireSucces.h"

class Personnage : public ObjetFixe{
private:
public:
	Personnage(unsigned int ID, gfx::Modele3D* modele, Vecteur3d position) : ObjetFixe(modele, ID, "personnage", position, Vecteur3d(), false, false) {}
};