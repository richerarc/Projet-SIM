#pragma once	
#include "Salle.h"
class Connecteur : public Salle(){		
private:
 		 
public:
	Connecteur(){}
	
	Connecteur(Modele3D modele, int ID) : public Salle(modele, ID){}
 		 
	
};
