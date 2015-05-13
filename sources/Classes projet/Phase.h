#pragma once 
#include "Gestionnaire2D.h"

class Phase{
	
public:
	
	bool pause;
	
	Phase(){
		pause = false;
	}

	virtual void rafraichir(float frameTime) = 0;

	virtual void remplir() = 0;

	virtual void defPause(bool pause) = 0;

	virtual void actualiserEchelle(Vecteur2f vecteurEchelle) = 0;

};