#pragma once
#include "Salle.h"
class Connecteur : Salle(){
private:

public:
	Connecteur(){}
	
	Connecteur(Vecteur3d Pos, Modele3D modele) : public Salle(Pos, modele){}

};