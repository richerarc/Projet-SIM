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

	bool boiteDansBoite(BoiteCollision<T> boite) {
		for (int i = 0; i < 8; ++i)
			if (pointDansBoite(boit.obtBoite()[i]))
				return true;
		
		return false;
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