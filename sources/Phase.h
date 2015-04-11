#pragma once 
#include "Gestionnaire2D.h"

class Phase{
protected:
	bool pause;
public:
	Phase(){
		pause = false;
	}

	virtual void afficher(gfx::Fenetre& fenetre) = 0;

	virtual void rafraichir() = 0;

	void pause(bool pause){
		pause = pause;
	}

};