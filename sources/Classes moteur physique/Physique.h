#pragma once

#include "Singleton.h"
#include "Vecteur3.h"
#include "Chrono.h"

class Physique : public Singleton<Physique>{
private:

	double gravite;
	double constanteDeFriction;
	double champsMagnetique;
	double sensibiliteMagnetique;
	Chrono temps;

public:

	Physique() {
		temps.partir();
		constanteDeFriction = 0.5;
		gravite = 9.8;
		champsMagnetique = 4;
		sensibiliteMagnetique = 0.0072;
	}

	double obtenirForceNormale(double Masse, Vecteur3d& Vitesse, Vecteur3d Normale) {

		return masse * gravite * SDL_cos(Vitesse->angleEntreVecteurs(Normale) - 90);

	}

	void appliquerGravite(Vecteur3d& vecteurVitesseObjet) {
		vecteurVitesseObjet.y -= gravite;
	}

	void appliquerVent(Vecteur3d& VecteurVitesseObjet) {
	
	}
	
	void appliquerFrottement(Objet& objet) {
		objet.vecteurVitesse -= constanteDeFriction * obtenirForceNormale(objet.masse, objet.vecteurPosition);
	}

	// Procédure qui applique la force d'attraction magnétique sur un objet
	//(La force du champs et la sensibilité magnétique de l'objet sont constant).
	void appliquerMagnetisme(double& masseObjet, Vecteur3d& positionObjet, Vecteur3d& vecteurVitesseObjet, Vecteur3d& positionAimant) {

	double distanceObjetAimant = sqrt(pow(positionAimant.x - positionObjet.x, 2) + pow(positionAimant.y - positionObjet.y, 2) + pow(positionAimant.z - positionObjet.z, 2));
	double accelerationMagnetique = (6 * sensibiliteMagnetique * champsMagnetique) / (masseObjet * distanceObjetAimant);

	Vecteur3d vecteurProportionnel = { positionAimant.x - positionObjet.x, positionAimant.y - positionObjet.y, positionAimant.z - positionObjet.z };
	vecteurProportionnel.normaliser();

	Vecteur3d vecteurAcceleration = { accelerationMagnetique, accelerationMagnetique, accelerationMagnetique };

	vecteurAcceleration.prodruitParUnVecteur(vecteurProportionnel);

	vecteurVitesseObjet += vecteurAcceleration;

	}
	
	double obtenirAnglePenduleSimple(double angleMaximal, double omega) {
		return angleMaximal * SDL_cos(omega * temps.obtenirTemps());
	}

	double distanceEntreDeuxPoints(Vecteur3d& point1, Vecteur3d& point2) {
		point1.normaliser();
		return SDL_sqrt(SDL_pow((point2.x - point1.x), 2) + SDL_pow((point2.y - point1.y), 2) + SDL_pow((point2.z - point1.z), 2));
	}

	double positionPointDroite(Vecteur3d& droite1, Vecteur3d& droite2, Vecteur3d& point, Vecteur3D& normale) {
		
		normale.normaliser();

		if (normale.x > normale.y && normale.x > normale.z) {
			
			return (droite2.y - droite1.y) * (point.z - droite1.z) - (droite2.z - droite1.z) * (point.y - droite1.y);
		}
		
		if (normale.y > normale.x && normale.y > normale.z) {

			return (droite2.x - droite1.x) * (point.z - droite1.z) - (droite2.z - droite1.z) * (point.x - droite1.x);
		}

		if (normale.z > normale.x && normale.z > normale.y) {
			
			return (droite2.x - droite1.x) * (point.y - droite1.y) - (droite2.y - droite1.y) * (point.x - droite1.x);
		}	
	}

	double obtenirEnergieCinetique(double masse, Vecteur3d& vecteurVitesseObjet) {
		return 0.5 * masse * SDL_pow(vecteurVitesseObjet.norme(), 2);
	}	
};
