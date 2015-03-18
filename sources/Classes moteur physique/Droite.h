#include "Vecteur3.h"

class Droite {
private:
	Vecteur3d point;
	Vecteur3d vecteurDirecteur;
public:
	Droite(Vecteur3d& point1, Vecteur3d& point2) {
		vecteurDirecteur = point1.produitVectoriel(point2);
		point = point1;
	}

	Vecteur3d obtenirPoint() {
		return point;
	}

	Vecteur3d obtenirVecteurDirecteur() {
		return vecteurDirecteur;
	}
};