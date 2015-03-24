#pragma once

#include "Vecteur3.h"
#include "Droite.h"
#include <iostream>
#include <math.h>

class Plan {
private:
	Vecteur3d normale;
	double d;
public:

	Plan() {}

	Plan(Vecteur3d& point1, Vecteur3d& point2, Vecteur3d& point3) {
		calculerPlan(point1, point2, point3);
	}

	bool insertionDroitePlan(Droite& droite, Vecteur3d& point) {
		if (normale.produitScalaire(droite.obtenirVecteurDirecteur()) != 0) {
			
			double nombre = (normale.x * droite.obtenirPoint().x) + (normale.y * droite.obtenirPoint().y) + (normale.z * droite.obtenirPoint().z) + d;
			double k = (normale.x * droite.obtenirVecteurDirecteur().x) + (normale.y * droite.obtenirVecteurDirecteur().y) + (normale.z * droite.obtenirVecteurDirecteur().z);

			k = -nombre / k;

			point = Vecteur3d((droite.obtenirPoint().x + (k * droite.obtenirVecteurDirecteur().x)), (droite.obtenirPoint().y + (k * droite.obtenirVecteurDirecteur().y)), (droite.obtenirPoint().z + (k * droite.obtenirVecteurDirecteur().z)));
			return true;
		}
		return false;
	}

	void calculerPlan(Vecteur3d& point1, Vecteur3d& point2, Vecteur3d& point3) {
		Vecteur3d u = point1 - point2;
		Vecteur3d v = point1 - point3;
		normale = u.produitVectoriel(v);
		d = -(normale.x * point1.x + normale.y * point1.y + normale.z * point1.z);
	}

	double obtenirAnglePlan() {
		return acos(normale.y / (normal.norme()));
	}

	Vecteur3d obtenirNormale() {
		return normale;
	}

	Vecteur3d obtenirD() {
		return d;
	}
};
