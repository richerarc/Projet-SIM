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
		retour.x = (obtXMax() - obtXMin()) / 2;
		retour.y = 0;
		retour.z = (obtZMax() - obtZMin()) / 2;

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
		return true /*(x >= obtXMin() && x <= obtXMax())*/;
	}

	bool pointDansBoiteY(double y) {
		return (y >= obtYMin() && y <= obtYMax());
	}

	bool pointDansBoiteZ(double z) {
		return (z >= obtZMin() && z <= obtZMax());
	}

	double obtXMin() {
		double xDebut = boiteCollision[0].x;
		double xAutre;
		do {
			xAutre = boiteCollision[rand() % 7 + 1].x;
		} while (xDebut == xAutre);

		return (xDebut < xAutre) ? xDebut : xAutre;
	}

	double obtXMax() {
		double xDebut = boiteCollision[0].x;
		double xAutre;
		do {
			xAutre = boiteCollision[rand() % 7 + 1].x;
		} while (xDebut == xAutre);

		return (xDebut > xAutre) ? xDebut : xAutre;
	}

	double obtYMin() {
		double yDebut = boiteCollision[0].y;
		double yAutre;
		do {
			yAutre = boiteCollision[rand() % 7 + 1].y;
		} while (yDebut == yAutre);

		return (yDebut < yAutre) ? yDebut : yAutre;
	}

	double obtYMax() {
		double yDebut = boiteCollision[0].y;
		double yAutre;
		do {
			yAutre = boiteCollision[rand() % 7 + 1].y;
		} while (yDebut == yAutre);

		return (yDebut > yAutre) ? yDebut : yAutre;
	}

	double obtZMin() {
		double zDebut = boiteCollision[0].z;
		double zAutre;
		do {
			zAutre = boiteCollision[rand() % 7 + 1].z;
		} while (zDebut == zAutre);

		return (zDebut < zAutre) ? zDebut : zAutre;
	}

	double obtZMax() {
		double zDebut = boiteCollision[0].z;
		double zAutre;
		do {
			zAutre = boiteCollision[rand() % 7 + 1].z;
		} while (zDebut == zAutre);

		return (zDebut > zAutre) ? zDebut : zAutre;
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