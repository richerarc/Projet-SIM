#pragma once

#include "Vecteur3.h"

class Physique {
private:

	double gravite;
	double constanteDeFriction;
	Chrono temps;

public:

	Physique() {
		temps.partir();
		constanteDeFriction = 0.5;
	}

	void appliquerGravite(Vecteur3d& vecteurVitesseObjet) {
		vecteurVitesseObjet.y -= gravite;
	}
	
	void appliquerFrottement(Objet& objet) {
		objet.vecteurVitesse -= constanteDeFriction * obtenirForceNormale(objet.masse, objet.vecteurPosition);
	}
	
	double obtenirAnglePenduleSimple(double& angleMaximal, double& omega) {
		return angleMaximal * SDL_cos(omega * temps.obtenirTemps());
	}

	double distanceEntreDeuxPoints(Vecteur3d& point1, Vecteur3d& point2) {
		point1.normaliser();
		return SDL_sqrt(SDL_pow((point2.x - point1.x), 2) + SDL_pow((point2.y - point1.y), 2) + SDL_pow((point2.z - point1.z), 2));
	}

	double obtenirEnergieCinetique(double& masse, Vecteur3d& vecteurVitesseObjet) {
		return 0.5 * masse * SDL_pow(vecteurVitesseObjet.norme(), 2);
	}

	double obtenirForceNormale(double& masse, Vecteur3d& position) {

	}
};