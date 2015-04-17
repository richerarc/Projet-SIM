#pragma once
#include "Vecteur3.h"

template<typename T>
class BoiteCollision{
private:
	Vecteur3<T> boiteCollision[8];
public:
	BoiteCollision(){}
	~BoiteCollision(){}

	BoiteCollision(Vecteur3<T>* _boiteCollision){
		for (int i = 0; i < 8; i++){
			boiteCollision[i] = _boiteCollision[i];
		}
	}

	Vecteur3<T>* obtBoite(){
		return boiteCollision;
	}
};