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

		Vecteur3<T> retour;
		retour.x = (obtXMax() - std::fabs(obtXMin())) / 2;
		retour.y = 0;
		retour.z = (obtZMax() - std::fabs(obtZMin())) / 2;

		return retour;
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

	bool pointDansBoite(Vecteur3d point) {
		return (pointDansBoiteX(point.x) && pointDansBoiteY(point.y) && pointDansBoiteZ(point.z));
	}

	bool pointDansBoiteX(double x) {
		return (x >= obtXMin() && x <= obtXMax());
	}

	bool pointDansBoiteY(double y) {
		return (y >= obtYMin() && y <= obtYMax());
	}

	bool pointDansBoiteZ(double z) {
		return (z >= obtZMin() && z <= obtZMax());
	}

	double obtXMin() {
		int xDebut = boiteCollision[0].x + 0.5f;
		int xAutre;
		int i;
		for (i = 1; i < 8; ++i){
			xAutre = boiteCollision[i].x + 0.5f;
			if (xAutre != xDebut)
				break;
		}
		return (xDebut < xAutre) ? boiteCollision[0].x : boiteCollision[i].x;
	}

	double obtXMax() {
		int xDebut = boiteCollision[0].x + 0.5f;
		int xAutre;
		int i;
		for (i = 1; i < 8; ++i){
			xAutre = boiteCollision[i].x + 0.5f;
			if (xAutre != xDebut)
				break;
		}
		return (xDebut > xAutre) ? boiteCollision[0].x : boiteCollision[i].x;
	}

	double obtYMin() {
		int yDebut = boiteCollision[0].y + 0.5f;
		int yAutre;
		int i;
		for (i = 1; i < 8; ++i){
			yAutre = boiteCollision[i].y + 0.5f;
			if (yAutre != yDebut)
				break;
		}
		return (yDebut < yAutre) ? boiteCollision[0].y : boiteCollision[i].y;
	}

	double obtYMax() {
		int yDebut = boiteCollision[0].y + 0.5f;
		int yAutre;
		int i;
		for (i = 1; i < 8; ++i){
			yAutre = boiteCollision[i].y + 0.5f;
			if (yAutre != yDebut)
				break;
		}
		return (yDebut > yAutre) ? boiteCollision[0].y : boiteCollision[i].y;
	}

	double obtZMin() {
		int zDebut = boiteCollision[0].z + 0.5f;
		int zAutre;
		int i;
		for (i = 1; i < 8; ++i){
			zAutre = boiteCollision[i].z + 0.5f;
			if (zAutre != zDebut)
				break;
		}
		return (zDebut < zAutre) ? boiteCollision[0].z : boiteCollision[i].z;
	}

	double obtZMax() {
		int zDebut = boiteCollision[0].z + 0.5f;
		int zAutre;
		int i;
		for (i = 1; i < 8; ++i){
			zAutre = boiteCollision[i].z + 0.5f;
			if (zAutre != zDebut)
				break;
		}
		return (zDebut > zAutre) ? boiteCollision[0].z : boiteCollision[i].z;
	}

	double obtGrandeurX() {
		return obtXMax() - obtXMin();
	}

	double obtGrandeurY() {
		return obtYMax() - obtYMin();
	}

	double obtGrandeurZ() {
		return obtZMax() - obtZMin();
	}
};