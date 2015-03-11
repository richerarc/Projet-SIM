#include "Vecteur3.h"
#include "Droite.h"
#include <iostream>
#include <math.h>

class Plan {
private:
	Vecteur3d normale;
	Vecteur3d d;
public:
	Plan(Vecteur3d& point1, Vecteur3d& point2, Vecteur3d& point3) {
		calculerPlan(point1, point2, point3);
	}

	Vecteur3d insertionDroitePlan(Droite& droite) {
		if (((normale.x * droite.obtenirVecteurDirecteur().x) + (normale.y * droite.obtenirVecteurDirecteur().y) + (normale.z * droite.obtenirVecteurDirecteur().z)) != 0) {
			Vecteur3d tmpVecteurDirecteur;
			Vecteur3d tmpPoint;
			double isolation;
			tmpPoint.x *= normale.x;
			tmpPoint.y *= normale.y;
			tmpPoint.z *= normale.z;
			tmpVecteurDirecteur.x *= normale.x;
			tmpVecteurDirecteur.y *= normale.y;
			tmpVecteurDirecteur.z *= normale.z;
			isolation = -1 * (tmpVecteurDirecteur.x + tmpVecteurDirecteur.y + tmpVecteurDirecteur.z);
			isolation -= (tmpPoint.x + tmpPoint.y + tmpPoint.z);
			return Vecteur3d((droite.obtenirPoint().x + (isolation * droite.obtenirVecteurDirecteur().x)), (droite.obtenirPoint().y + (isolation * droite.obtenirVecteurDirecteur().y)), (droite.obtenirPoint().z + (isolation * droite.obtenirVecteurDirecteur().z)));
		}
		else {
			return NULL;
		}
	}

	void calculerPlan(Vecteur3d& point1, Vecteur3d& point2, Vecteur3d& point3) {
		Vecteur3d u = point1 - point2;
		Vecteur3d v = point1 - point3;
		normale = u.produitVectoriel(v);
		d.x = u.x * point1.x;
		d.y = u.y * point1.y;
		d.z = u.z * point1.z;
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