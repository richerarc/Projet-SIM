#pragma once

#include "Singleton.h"
#include "Vecteur3.h"
#include "Chrono.h"
#include "Droite.h"
#include "Plan.h"

class Physique : public Singleton<Physique>{
private:

	double gravite;
	double constanteDeFriction;
	double champsMagnetique;
	double sensibiliteMagnetique;
	float frametime;
	std::map<char*, double> mapRestitution;
	Chrono temps;

	bool collisionDroiteModele(gfx::Modele3D& modele3D, Droite& rayonCollision, Vecteur3d& pointCollision, Vecteur3d& normale) {

		double resultat1, resultat2, resultat3;
		Vecteur3d point1;
		Vecteur3d point2;
		Vecteur3d point3;
		double* tabVertices;
		Plan plan;

		gfx::Modele& modele = modele3D.obtModele();

		tabVertices = modele3D.obtSommetsModifies();

		for (unsigned int Nbrface = 0; Nbrface < modele.obtNbrFaces(); Nbrface++) {

			for (int j = 0; j < 3; j++) {
				switch (j) {

				case 0:
					point1 = { tabVertices[(j + Nbrface) * 3], tabVertices[(j + Nbrface) * 3 + 1], tabVertices[(j + Nbrface) * 3 + 2] };
					break;

				case 1:
					point2 = { tabVertices[(j + Nbrface) * 3], tabVertices[(j + Nbrface) * 3 + 1], tabVertices[(j + Nbrface) * 3 + 2] };
					break;

				case 2:
					point3 = { tabVertices[(j + Nbrface) * 3], tabVertices[(j + Nbrface) * 3 + 1], tabVertices[(j + Nbrface) * 3 + 2] };
					break;
				}
			}

			plan.calculerPlan(point1, point2, point3);

			if (plan.insertionDroitePlan(rayonCollision, pointCollision)) {

				if (pointDansTriangle(point1, point2, point3, pointCollision)) {
					normale = { modele.obtNormales()[Nbrface * 3], modele.obtNormales()[Nbrface * 3 + 1], modele.obtNormales()[Nbrface * 3 + 2] };
					return true;
				}
			}
		}
		return false;
	}

public:

	Physique() {
		frametime = temps.repartir().enSecondes();
		constanteDeFriction = 0.5;
		gravite = -9.8;
		champsMagnetique = 4;
		sensibiliteMagnetique = 0.0072;

		// Ajout des coefficients de restitution des différents matériaux
		mapRestitution["metal"] = 0.9;
		mapRestitution["bois"] = 0.5;
		mapRestitution["plastic"] = 0.68;
		mapRestitution["ballerebondissante"] = 0.1;
	}

	void repartirTemps() {
		frametime = temps.repartir().enSecondes();
	}

	
	void RebondObjetCarte(gfx::Modele3D& objet1, Vecteur3d vecteurNormal) {

		double dScalaire = (2 - mapRestitution[objet1.obtMateriel()]) * objet1.obtVitesse().produitScalaire(vecteurNormal);
		objet1.obtVitesse() -= vecteurNormal * dScalaire;
	}

void RebondObjetObjet(gfx::Modele3D& objet1, gfx::Modele3D& objet2, Vecteur3d vecteurNormal) {

		Vecteur3d vVitesseRelative = objet1.obtVitesse() - objet2.obtVitesse();

		double e = (mapRestitution[objet1.obtMateriel()] + mapRestitution[objet2.obtMateriel()]) / 2; // Moyenne des coefficients de restitution

		double j = (-(1 + e) * (vVitesseRelative.produitScalaire(vecteurNormal))) / ((vecteurNormal.produitScalaire(vecteurNormal)) * (1 / objet1.obtMasse() + 1 / objet2.obtMasse()));

		Vecteur3d vecteurNormal2 = vecteurNormal;

		vecteurNormal *= j / objet1.obtMasse();
		objet1.obtVitesse() += vecteurNormal;

		vecteurNormal2 *= j / objet2.obtMasse();
		objet2.obtVitesse() -= vecteurNormal2;
	}
	
	double obtenirForceNormale(double masse, Vecteur3d& vitesse, Vecteur3d normale) {

		return masse * gravite * SDL_cos(vitesse.angleEntreVecteurs(normale) - 90);
	}

	void appliquerGravite(Vecteur3d &vecteurVitesseObjet) {
		vecteurVitesseObjet.y += gravite * frametime;
	}

	void AppliquerVent(Vecteur3d vecteurVitesseVent, gfx::Modele3D& objet) {

		float* tableauNormales = objet.obtModele().obtNormales();
		float* tableauVertices = objet.obtModele().obtVertices();

		double accelerationSelonForceVent = 0.5 * 1.204 * pow(vecteurVitesseVent.norme(), 2);

		double coefficientTrainer = 0;
		double surface = 0;

		double nombreFace = objet.obtModele().obtNbrFaces() * 3;

		unsigned int nombreFaceSousPression = 0;

		// Boucle sur toutes les faces de l'objet
		for (unsigned int parcoursFace = 0; parcoursFace < nombreFace;) {

			// Vecteur normal de la face selon une moyenne de ceux des vertices.
			Vecteur3d vecteurNormale = { (tableauNormales[parcoursFace] + tableauNormales[parcoursFace + 3] + tableauNormales[parcoursFace + 6]) / 3,
				(tableauNormales[parcoursFace + 1] + tableauNormales[parcoursFace + 4] + tableauNormales[parcoursFace + 7]) / 3,
				(tableauNormales[parcoursFace + 2] + tableauNormales[parcoursFace + 5] + tableauNormales[parcoursFace + 8]) / 3 };

			double angleEntreVecteursVentNormale = (vecteurVitesseVent.produitScalaire(vecteurNormale)) / (vecteurVitesseVent.norme() * vecteurNormale.norme());

			// Si l'angle entre le vecteur normal et le vecteur du vent est négatif
			if (angleEntreVecteursVentNormale < 0) {

				coefficientTrainer += abs(angleEntreVecteursVentNormale);
				// Calcul de la surface selon la formule d'héron: sqrt(s(s-a)(s-b)(s-c))

				// a : Point 1 à point 2;
				double a = sqrt(pow(tableauVertices[parcoursFace] - tableauVertices[parcoursFace + 3], 2) +
					pow(tableauVertices[parcoursFace + 1] - tableauVertices[parcoursFace + 4], 2) +
					pow(tableauVertices[parcoursFace + 2] - tableauVertices[parcoursFace + 5], 2));

				// a : Point 1 à point 3;
				double b = sqrt(pow(tableauVertices[parcoursFace] - tableauVertices[parcoursFace + 6], 2) +
					pow(tableauVertices[parcoursFace + 1] - tableauVertices[parcoursFace + 7], 2) +
					pow(tableauVertices[parcoursFace + 2] - tableauVertices[parcoursFace + 8], 2));

				// a : Point 2 à point 3;
				double c = sqrt(pow(tableauVertices[parcoursFace + 3] - tableauVertices[parcoursFace + 6], 2) +
					pow(tableauVertices[parcoursFace + 4] - tableauVertices[parcoursFace + 7], 2) +
					pow(tableauVertices[parcoursFace + 5] - tableauVertices[parcoursFace + 8], 2));

				// Demi-périmètre;
				double s = 0.5 * (a + b + c);

				surface += sqrt(s*(s - a)*(s - b)*(s - c));

				nombreFaceSousPression++;

			}
			parcoursFace += 9; // Prochaine face(3vertice*xyz)
		}

		coefficientTrainer /= nombreFaceSousPression;

		// Fin du calcul...
		accelerationSelonForceVent *= (coefficientTrainer * surface / objet.obtMasse());

		// Mise en proportion pour l'addition...
		vecteurVitesseVent.normaliser();

		// Nécéssite l'ajout d'un division par le temps...
		Vecteur3d vecteurVitesseAppliquer = { accelerationSelonForceVent * vecteurVitesseVent.x, accelerationSelonForceVent * vecteurVitesseVent.y, accelerationSelonForceVent * vecteurVitesseVent.z };

		objet.obtVitesse() += vecteurVitesseAppliquer * frametime;
	}
	
	// MANQUE LA NORMALE
	void appliquerFrottement(gfx::Modele3D& objet) {
		//objet.obtVitesse().soustraire(constanteDeFriction * obtenirForceNormale(objet.obtMasse(), objet.obtPosition()));
	}
	
	// Procédure qui applique la force d'attraction magnétique sur un objet
	// (La force du champs et la sensibilité magnétique de l'objet sont constant).
	void appliquerMagnetisme(gfx::modele3D& objet, Vecteur3d positionAimant) {

		double distanceObjetAimant = distanceEntreDeuxPoints(positionAimant, objet.obtPosition());
		double accelerationMagnetique = (6 * sensibiliteMagnetique * champsMagnetique) / (objet.obtMasse() * distanceObjetAimant);

		Vecteur3d vecteurProportionnel = { positionAimant.x - objet.obtPosition().x, positionAimant.y - objet.obtPosition().y, positionAimant.z - objet.obtPosition().z };
		vecteurProportionnel.normaliser();

		Vecteur3d vecteurAcceleration = { accelerationMagnetique, accelerationMagnetique, accelerationMagnetique };

		vecteurAcceleration.prodruitParUnVecteur(vecteurProportionnel);

		objet.obtVitesse() += vecteurAcceleration * frametime;

	}
	
	double obtenirAnglePenduleSimple(double angleMaximal, double omega) {
		return angleMaximal * SDL_cos(omega * frametime);
	}

	double distanceEntreDeuxPoints(Vecteur3d& point1, Vecteur3d& point2) {
		return SDL_sqrt(SDL_pow((point2.x - point1.x), 2) + SDL_pow((point2.y - point1.y), 2) + SDL_pow((point2.z - point1.z), 2));
	}

	double positionPointDroite(Vecteur3d& droite1, Vecteur3d& droite2, Vecteur3d& point, Vecteur3d& normale) {
		
		Vecteur3d vect1 = point3 - point1;
		Vecteur3d vect2 = point2 - point1;
		Vecteur3d vect3 = point - point1;

		double produit11 = vect1.produitScalaire(vect1);
		double produit12 = vect1.produitScalaire(vect2);
		double produit13 = vect1.produitScalaire(vect3);
		double produit22 = vect2.produitScalaire(vect2);
		double produit23 = vect2.produitScalaire(vect3);

		double invDenom = 1 / (produit11 * produit22 - produit12 * produit12);
		double u = (produit22 * produit13 - produit12 * produit23) * invDenom;
		double v = (produit11 * produit23 - produit23 * produit13) * invDenom;

		return (u >= 0) && (v >= 0) && (u + v < 1);

	}

	double obtenirEnergieCinetique(double masse, Vecteur3d& vecteurVitesseObjet) {
		return 0.5 * masse * SDL_pow(vecteurVitesseObjet.norme(), 2);
	}

	bool collisionObjetSalle(gfx::Modele3D& objet, Salle& salle) {
		Droite rayonCollision;
		Vecteur3d pointCollision;
		Vecteur3d point;
		Vecteur3d normale;
		double distance;
		double d;
		Vecteur3d* tabObjet = objet.obtBoiteDeCollisionModifiee();


		for (int i = 0; i < 8; i++) {

			point = tabObjet[i];

			rayonCollision = Droite(point, objet.obtVitesse());

			if (collisionDroiteModele(salle.obtModele(), rayonCollision, pointCollision, normale)) {

				if (normale.y > 0 && pointCollision.y > point.y && objet.obtVitesse().y < 0) {
					normale.normaliser();
					RebondObjetCarte(objet, normale);
					return true;
				}

			}
		}
		return false;
	}

};
