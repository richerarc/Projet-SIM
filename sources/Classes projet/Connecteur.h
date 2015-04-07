#pragma once	
#include "Salle.h"
class Connecteur : public Salle{
private:

public:
	Connecteur(){}

	Connecteur(gfx::Modele3D& modele, int ID, unsigned int nbrPorte) : Salle(modele, nbrPorte, ID){}


};
