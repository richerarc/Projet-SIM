#pragma once
#include "Vecteur3.h"

class BoiteCollision{
private:
	Vecteur3<double> boiteCollision[8];
public:
	BoiteCollision(){}
	~BoiteCollision(){
		delete[] boiteCollision;
	}

	BoiteCollision(Vecteur3<double>* _boiteCollision){
		for (int i = 0; i < 8; i++){
			boiteCollision[i] = _boiteCollision[i];
		}
	}

	Vecteur3<double>* obtBoite(){
		return boiteCollision;
	}
};