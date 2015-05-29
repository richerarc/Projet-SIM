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

	Vecteur3<T> obtCentreBoite() {

		Vecteur3<T> positionCM = { 0, 0, 0 };

		for (unsigned int i = 0; i < 8; i++) {
			positionCM.x += boiteCollision[i].x;
			positionCM.y += boiteCollision[i].y;
			positionCM.z += boiteCollision[i].z;
		}

		positionCM /= 8;

		return positionCM;
	}

	Vecteur3<T> distanceEntreDeuxCentre(BoiteCollision<T> boite) {

		Vecteur3<T> point1 = obtCentreBoite();
		Vecteur3<T> point2 = boite.obtCentreBoite();
		Vecteur3<T> retour;

		retour.x = point1.x - point2.x;
		retour.y = point1.y - point2.y;
		retour.z = point1.z - point2.z;

		return retour;

	}

	bool boiteDansBoite(BoiteCollision<T> boite) {
		int temp(0);
		for (int i = 0; i < 8; ++i)
			if (pointDansBoite(boite.obtBoite()[i]))
				++temp;
		return temp == 8;
	}

	bool collisionDeuxBoite(BoiteCollision<T> boite) {
		Vecteur3<T> pointBoite;
		for (int i = 0; i < 8; ++i) {
			pointBoite = boite.obtBoite()[i];
			if (this->pointDansBoite(pointBoite))
				return true;
		}
		for (int i = 0; i < 8; ++i) {
			pointBoite = this->obtBoite()[i];
			if (boite.pointDansBoite(pointBoite))
				return true;
		}
		return false;
	}

	bool pointDansBoite(Vecteur3d point) {
		return (pointDansBoiteX(point.x) && pointDansBoiteY(point.y) && pointDansBoiteZ(point.z));
	}

	bool pointDansBoiteX(T x) {
		return (x >= obtXMin() && x <= obtXMax());
	}

	bool pointDansBoiteY(T y) {
		return (y >= obtYMin() && y <= obtYMax());
	}

	bool pointDansBoiteZ(T z) {
		return (z >= obtZMin() && z <= obtZMax());
	}

	T obtXMin() {
		T xDebut = boiteCollision[0].x;
		T xAutre;
		for (int i = 1; i < 8; ++i){
			xAutre = boiteCollision[i].x;
			if (xAutre != xDebut)
				return (xDebut < xAutre) ? boiteCollision[0].x : boiteCollision[i].x;
		}
	}

	T obtXMax() {
		T xDebut = boiteCollision[0].x;
		T xAutre;
		for (int i = 1; i < 8; ++i){
			xAutre = boiteCollision[i].x;
			if (xAutre != xDebut)
				return (xDebut > xAutre) ? boiteCollision[0].x : boiteCollision[i].x;
		}
	}

	T obtYMin() {
		T yDebut = boiteCollision[0].y;
		T yAutre;
		for (int i = 1; i < 8; ++i){
			yAutre = boiteCollision[i].y;
			if (yAutre != yDebut)
				return (yDebut < yAutre) ? boiteCollision[0].y : boiteCollision[i].y;
		}
	}

	T obtYMax() {
		T yDebut = boiteCollision[0].y;
		T yAutre;
		for (int i = 1; i < 8; ++i){
			yAutre = boiteCollision[i].y;
			if (yAutre != yDebut)
				return (yDebut > yAutre) ? boiteCollision[0].y : boiteCollision[i].y;
		}
	}

	T obtZMin() {
		T zDebut = boiteCollision[0].z;
		T zAutre;
		for (int i = 1; i < 8; ++i){
			zAutre = boiteCollision[i].z;
			if (zAutre != zDebut)
				return (zDebut < zAutre) ? boiteCollision[0].z : boiteCollision[i].z;
		}
	}

	T obtZMax() {
		T zDebut = boiteCollision[0].z;
		T zAutre;
		for (int i = 1; i < 8; ++i){
			zAutre = boiteCollision[i].z;
			if (zAutre != zDebut)
				return (zDebut > zAutre) ? boiteCollision[0].z : boiteCollision[i].z;
		}
	}

	T obtGrandeurX() {
		return obtXMax() - obtXMin();
	}

	T obtGrandeurY() {
		return obtYMax() - obtYMin();
	}

	T obtGrandeurZ() {
		return obtZMax() - obtZMin();
	}
};