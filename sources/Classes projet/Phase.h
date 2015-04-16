#pragma once 
#include "Gestionnaire2D.h"

class Phase{
protected:
	bool pause;
public:
	Phase(){
		pause = false;
	}

	virtual void rafraichir(float frameTime) = 0;

	void defPause(bool pause){
		this->pause = pause;
	}

};