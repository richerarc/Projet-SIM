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

		Vecteur3<T> retour;
		retour.x = (obtXMax() + obtXMin()) / 2;
		retour.y = (obtYMax() + obtYMin()) / 2;
		retour.z = (obtZMax() + obtZMin()) / 2;

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

	bool collisionDeuxBoite(BoiteCollision<T> boite) {
		Vecteur3d pointBoite;
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