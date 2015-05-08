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
		retour.x = (obtXMax() - fabs(obtXMin())) / 2;
		retour.y = 0;
		retour.z = (obtZMax() - fabs(obtZMin())) / 2;

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
		int xDebut = boiteCollision[0].x + 0.5;
		int xAutre;
		int rando;
		do {
			rando = rand() % 7 + 1;
			xAutre = boiteCollision[rando].x + 0.5;
		} while (xDebut == xAutre);

		return (xDebut < xAutre) ? boiteCollision[0].x : boiteCollision[rando].x;
	}

	double obtXMax() {
		int xDebut = boiteCollision[0].x + 0.5;
		int xAutre;
		int rando;
		do {
			rando = rand() % 7 + 1;
			xAutre = boiteCollision[rando].x + 0.5;
		} while (xDebut == xAutre);

		return (xDebut > xAutre) ? boiteCollision[0].x : boiteCollision[rando].x;
	}

	double obtYMin() {
		int yDebut = boiteCollision[0].y + 0.5;
		int yAutre;
		int rando;
		do {
			rando = rand() % 7 + 1;
			yAutre = boiteCollision[rando].y + 0.5;
		} while (yDebut == yAutre);

		return (yDebut < yAutre) ? boiteCollision[0].y : boiteCollision[rando].y;
	}

	double obtYMax() {
		int yDebut = boiteCollision[0].y + 0.5;
		int yAutre;
		int rando;
		do {
			rando = rand() % 7 + 1;
			yAutre = boiteCollision[rando].y + 0.5;
		} while (yDebut == yAutre);

		return (yDebut > yAutre) ? boiteCollision[0].y : boiteCollision[rando].y;
	}

	double obtZMin() {
		int zDebut = boiteCollision[0].z + 0.5;
		int zAutre;
		int rando;
		do {
			rando = rand() % 7 + 1;
			zAutre = boiteCollision[rando].z + 0.5;
		} while (zDebut == zAutre);

		return (zDebut < zAutre) ? boiteCollision[0].z : boiteCollision[rando].z;
	}

	double obtZMax() {
		int zDebut = boiteCollision[0].z + 0.5;
		int zAutre;
		int rando;
		do {
			rando = rand() % 7 + 1;
			zAutre = boiteCollision[rando].z + 0.5;
		} while (zDebut == zAutre);

		return (zDebut > zAutre) ? boiteCollision[0].z : boiteCollision[rando].z;
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