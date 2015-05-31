#pragma once
#include "Vecteur3.h"
#include "Plan.h"

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

	bool pointDansBoite(Vecteur3d point, Droite rayonCollision, Vecteur3d &normale, Vecteur3d vitesse, Vecteur3d &pointCollision) {
		bool collision = (pointDansBoiteX(point.x) && pointDansBoiteY(point.y) && pointDansBoiteZ(point.z));
		if (collision) {
			double distanceX = fabs(obtBoite()[0].x - point.x);
			double distanceY = fabs(obtBoite()[0].y - point.y);
			double distanceZ = fabs(obtBoite()[0].z - point.z);
			Vecteur3<T> point1X, point2X, point3X, point1Y, point2Y, point3Y, point1Z, point2Z, point3Z, pointBoite, pointPlan1, pointPlan2, pointPlan3;
			pointBoite = obtBoite()[0];
			Plan plan1, plan2, plan3;
			bool collision = false;
			for (int h = 0; h < 3; ++h) {
				std::vector<Vecteur3d> listePoint;
				auto it = listePoint.begin();
				for (int g = 0; g < 8; ++g)
					listePoint.push_back(obtBoite()[g]);
				for (int i = 0; i < 3; ++i) {
					for (int j = 0; j < listePoint.size(); ++j) {
						if (h == 0) {
							if (fabs(listePoint[j].x - point.x) < distanceX) {
								distanceX = fabs(listePoint[j].x - point.x);
								pointBoite = listePoint[j];
								it = listePoint.begin();
								std::advance(it, j);
								collision = true;
							}
						}
						if (h == 1) {
							if (fabs(listePoint[j].y - point.y) < distanceY) {
								distanceY = fabs(listePoint[j].y - point.y);
								pointBoite = listePoint[j];
								it = listePoint.begin();
								std::advance(it, j);
								collision = true;
							}
						}
						if (h == 2) {
							if (fabs(listePoint[j].z - point.z) < distanceZ) {
								distanceZ = fabs(listePoint[j].z - point.z);
								pointBoite = listePoint[j];
								it = listePoint.begin();
								std::advance(it, j);
								collision = true;
							}
						}
						if ((j == listePoint.size() - 1) && !collision) {
							it = listePoint.begin();
							pointBoite = listePoint[0];
						}
					}

					listePoint.erase(it);
					it = listePoint.begin();
					if (i == 0 && h == 0) {
						point1X = pointBoite;
					}
					else if (i == 1 && h == 0) {
						point2X = pointBoite;
					}
					else if (i == 2 && h == 0) {
						point3X = pointBoite;
					}
					else if (i == 0 && h == 1) {
						point1Y = pointBoite;
					}
					else if (i == 1 && h == 1) {
						point2Y = pointBoite;
					}
					else if (i == 2 && h == 1) {
						point3Y = pointBoite;
					}
					else if (i == 0 && h == 2) {
						point1Z = pointBoite;
					}
					else if (i == 1 && h == 2) {
						point2Z = pointBoite;
					}
					else if (i == 2 && h == 2) {
						point3Z = pointBoite;
					}
					if (h == 0)
						distanceX = fabs(listePoint[0].x - point.x);
					else if (h == 1)
						distanceY = fabs(listePoint[0].y - point.y);
					else if (h == 2)
						distanceZ = fabs(listePoint[0].z - point.z);
					collision = false;
				}
			}
			plan1 = Plan(point1X, point2X, point3X);
			plan2 = Plan(point1Y, point2Y, point3Y);
			plan3 = Plan(point1Z, point2Z, point3Z);

			bool inversement = false;
			Plan planNormale;

			rayonCollision = Droite(point, vitesse);

			bool collision1, collision2, collision3;

			collision1 = plan1.insertionDroitePlan(rayonCollision, pointPlan1);
			collision2 = plan2.insertionDroitePlan(rayonCollision, pointPlan2);
			collision3 = plan3.insertionDroitePlan(rayonCollision, pointPlan3);

			distanceX = Maths::distanceEntreDeuxPoints(pointPlan1, point);
			distanceY = Maths::distanceEntreDeuxPoints(pointPlan2, point);
			distanceZ = Maths::distanceEntreDeuxPoints(pointPlan3, point);

			if (collision1 && (distanceX < distanceY) && (distanceX < distanceZ)) {
				planNormale = Plan(point1X, point2X, point3X);
				pointCollision = Vecteur3d((pointPlan1.x - point.x) + point.x, point.y, point.z);
				if ((planNormale.obtenirNormale().x < 0 && vitesse.x < 0) || (planNormale.obtenirNormale().x > 0 && vitesse.x > 0))
					inversement = true;
			}
			else if (collision2 && (distanceY < distanceX) && (distanceY < distanceZ)) {
				planNormale = Plan(point1Y, point2Y, point3Y);
				pointCollision = Vecteur3d(point.x, (pointPlan2.y - point.y) + point.y, point.z);
				if ((planNormale.obtenirNormale().y < 0 && vitesse.y < 0) || (planNormale.obtenirNormale().y > 0 && vitesse.y > 0))
					inversement = true;
			}
			else if (collision3 && (distanceZ < distanceY) && (distanceZ < distanceX)) {
				planNormale = Plan(point1Z, point2Z, point3Z);
				pointCollision = Vecteur3d(point.x, point.y, (pointPlan3.z - point.z) + point.z);
				if ((planNormale.obtenirNormale().z < 0 && vitesse.z < 0) || (planNormale.obtenirNormale().z > 0 && vitesse.z > 0))
					inversement = true;
			}
			normale = planNormale.obtenirNormale();
			normale.normaliser();
			if (inversement)
				normale.inverser();

		}
		return collision;
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

	double obtXMin() {
		int xDebut = boiteCollision[0].x + 0.5f;
		int xAutre;
		int i;
		for (i = 1; i < 8; ++i){
			xAutre = boiteCollision[i].x + 0.5f;
			if (xAutre != xDebut)
				return (xDebut < xAutre) ? boiteCollision[0].x : boiteCollision[i].x;
		}
		return NULL;
	}

	T obtXMax() {
		int xDebut = boiteCollision[0].x + 0.5f;
		int xAutre;
		int i;
		for (i = 1; i < 8; ++i){
			xAutre = boiteCollision[i].x + 0.5f;
			if (xAutre != xDebut)
				return (xDebut > xAutre) ? boiteCollision[0].x : boiteCollision[i].x;
		}
		return NULL;
	}

	T obtYMin() {
		int yDebut = boiteCollision[0].y + 0.5f;
		int yAutre;
		int i;
		for (i = 1; i < 8; ++i){
			yAutre = boiteCollision[i].y + 0.5f;
			if (yAutre != yDebut)
				return (yDebut < yAutre) ? boiteCollision[0].y : boiteCollision[i].y;
		}
		return NULL;
	}

	T obtYMax() {
		int yDebut = boiteCollision[0].y + 0.5f;
		int yAutre;
		int i;
		for (i = 1; i < 8; ++i){
			yAutre = boiteCollision[i].y + 0.5f;
			if (yAutre != yDebut)
				return (yDebut > yAutre) ? boiteCollision[0].y : boiteCollision[i].y;
		}
		return NULL;
	}

	T obtZMin() {
		int zDebut = boiteCollision[0].z + 0.5f;
		int zAutre;
		int i;
		for (i = 1; i < 8; ++i){
			zAutre = boiteCollision[i].z + 0.5f;
			if (zAutre != zDebut)
				return (zDebut < zAutre) ? boiteCollision[0].z : boiteCollision[i].z;
		}
		return NULL;
	}

	T obtZMax() {
		int zDebut = boiteCollision[0].z + 0.5f;
		int zAutre;
		int i;
		for (i = 1; i < 8; ++i){
			zAutre = boiteCollision[i].z + 0.5f;
			if (zAutre != zDebut)
				return (zDebut > zAutre) ? boiteCollision[0].z : boiteCollision[i].z;
		}
		return NULL;
	}

	T obtXMin2() {
		T pointX = boiteCollision[0].x;
		T pointMinX = boiteCollision[0].x;
		for (int i = 0; i < 8; ++i) {
			pointX = boiteCollision[i].x;
			if (pointX < pointMinX) {
				pointMinX = pointX;
			}
		}
		return pointMinX;
	}

	T obtXMax2() {
		T pointX = boiteCollision[0].x;
		T pointMaxX = boiteCollision[0].x;
		for (int i = 0; i < 8; ++i) {
			pointX = boiteCollision[i].x;
			if (pointX > pointMaxX) {
				pointMaxX = pointX;
			}
		}
		return pointMaxX;
	}

	T obtYMin2() {
		T pointY = boiteCollision[0].y;
		T pointMinY = boiteCollision[0].y;
		for (int i = 0; i < 8; ++i) {
			pointY = boiteCollision[i].y;
			if (pointY < pointMinY) {
				pointMinY = pointY;
			}
		}
		return pointMinY;
	}

	T obtYMax2() {
		T pointY = boiteCollision[0].y;
		T pointMaxY = boiteCollision[0].y;
		for (int i = 0; i < 8; ++i) {
			pointY = boiteCollision[i].y;
			if (pointY > pointMaxY) {
				pointMaxY = pointY;
			}
		}
		return pointMaxY;
	}

	T obtZMin2() {
		T pointZ = boiteCollision[0].z;
		T pointMinZ = boiteCollision[0].z;
		for (int i = 0; i < 8; ++i) {
			pointZ = boiteCollision[i].z;
			if (pointZ < pointMinZ) {
				pointMinZ = pointZ;
			}
		}
		return pointMinZ;
	}

	T obtZMax2() {
		T pointZ = boiteCollision[0].z;
		T pointMaxZ = boiteCollision[0].z;
		for (int i = 0; i < 8; ++i) {
			pointZ = boiteCollision[i].z;
			if (pointZ > pointMaxZ) {
				pointMaxZ = pointZ;
			}
		}
		return pointMaxZ;
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