#pragma once
#include "Maths.h"
#include "Singleton.h"
#include "Vecteur3.h"
#include "Chrono.h"
#include "Droite.h"
#include "Plan.h"
#include "Vent.h"
#include "Aimant.h"
#include "Pendule.h"
#include <string>

enum collision{ AUCUNE, MUR, SOLDROIT, SOLCROCHE, PLAFOND };

class Physique : public Singleton < Physique > {
private:

	double gravite;
	double constanteDeFriction;
	double sensibiliteMagnetique;
	std::map<char*, double> mapRestitution;
	bool collision;

	bool collisionDroiteModele(gfx::Modele3D* modele3D, Droite& rayonCollision, Vecteur3d& pointCollision, Vecteur3d& normale, Vecteur3d* verticesPlan) {

		Vecteur3d point1;
		Vecteur3d point2;
		Vecteur3d point3;
		Vecteur3d point;
		double* tabVertices;
		double scalaire;
		Plan plan;

		gfx::Modele* modele = modele3D->obtModele();

		tabVertices = modele3D->obtSommetsModifies();

		for (unsigned int Nbrface = 0; Nbrface < modele->obtNbrSommets(); Nbrface += 3) {

			for (int j = 0; j < 3; j++) {
				switch (j) {

				case 0:
					point1 = { tabVertices[(Nbrface)* 3], tabVertices[(Nbrface)* 3 + 1], tabVertices[(Nbrface)* 3 + 2] };
					break;

				case 1:
					point2 = { tabVertices[(Nbrface)* 3 + 3], tabVertices[(Nbrface)* 3 + 4], tabVertices[(Nbrface)* 3 + 5] };
					break;

				case 2:
					point3 = { tabVertices[(Nbrface)* 3 + 6], tabVertices[(Nbrface)* 3 + 7], tabVertices[(Nbrface)* 3 + 8] };
					break;
				}
			}

			plan.calculerPlan(point1, point2, point3);

			normale = { modele3D->obtNormalesModifies()[Nbrface * 3], modele3D->obtNormalesModifies()[Nbrface * 3 + 1], modele3D->obtNormalesModifies()[Nbrface * 3 + 2] };
			if (plan.insertionDroitePlan(rayonCollision, pointCollision)) {
				if (abs(normale.x == abs(normale.z))) {
					normale.z += 0.01;
				}
				if (Maths::pointDansFace1(point1, point2, point3, pointCollision, normale) && Maths::pointDansFace(pointCollision, point1, point2, point3)) {

					point = pointCollision + rayonCollision.obtenirVecteurDirecteur();

					if (Maths::memeCote(point, rayonCollision.obtenirPoint(), pointCollision, point1)) {
						normale.normaliser();
						rayonCollision.obtenirVecteurDirecteur().normaliser();
						scalaire = normale.produitScalaire(rayonCollision.obtenirVecteurDirecteur());
						if (scalaire < 0 && (Maths::distanceEntreDeuxPoints(pointCollision, rayonCollision.obtenirPoint()) < 1)){
							verticesPlan[0] = point1;
							verticesPlan[1] = point2;
							verticesPlan[2] = point3;
							return true;
						}
					}
				}
			}
		}
		verticesPlan = nullptr;
		return false;
	}

	bool collisionDroiteObjet(Objet& objet, Droite& rayonCollision, Vecteur3d& pointCollision, Vecteur3d& normale) {

		Vecteur3d point1;
		Vecteur3d point2;
		Vecteur3d point3;
		Vecteur3d point;
		Vecteur3d* boiteCollision = objet.obtModele3D()->obtBoiteDeCollisionModifiee();
		Plan plan;
		Vecteur3i* indices = objet.obtModele3D()->obtModele()->obtIndidesBoiteDeCollision();
		Vecteur3i* normales = objet.obtModele3D()->obtModele()->obtNormalesBoiteDeCollision();

		for (unsigned int nbrFace = 0; nbrFace < 12; nbrFace++) {

			for (int j = 0; j < 3; j++) {
				switch (j) {

				case 0:
					point1 = boiteCollision[indices[nbrFace].x];
					break;

				case 1:
					point2 = boiteCollision[indices[nbrFace].y];
					break;

				case 2:
					point3 = boiteCollision[indices[nbrFace].z];
					break;
				}
			}

			normale.x = normales[nbrFace / 2].x;
			normale.y = normales[nbrFace / 2].y;
			normale.z = normales[nbrFace / 2].z;

			plan.calculerPlan(point1, point2, point3);
			if (plan.insertionDroitePlan(rayonCollision, pointCollision)) {

				if (Maths::pointDansFace1(point1, point2, point3, pointCollision, normale)) {

					point = pointCollision + rayonCollision.obtenirVecteurDirecteur();

					if (Maths::memeCote(point, rayonCollision.obtenirPoint(), pointCollision, point1)) {

						double angle = Maths::radianADegre(normale.angleEntreVecteurs(rayonCollision.obtenirVecteurDirecteur()));

						if (angle > 120 && angle < 240)
							return true;
					}
				}
			}
		}
		return false;
	}

public:

	Physique() {
		constanteDeFriction = 0.5;
		gravite = -9.8;
		sensibiliteMagnetique = 0.0072;
		collision = false;

		// Ajout des coefficients de restitution des différents matériaux
		mapRestitution["metal"] = 0.9;
		mapRestitution["bois"] = 0.5;
		mapRestitution["plastic"] = 0.68;
		mapRestitution["ballerebondissante"] = 0.1;
	}

	void appliquerPhysiqueSurListeObjet(gfx::Modele3D* modeleSalle, std::list<Objet*> objets, float frameTime, double temps) {
		for (auto it : objets) {
			Vent* it_Vent = dynamic_cast<Vent*>(it);
			if (it_Vent != nullptr) {
				for (auto it_Objet : objets) {
					if (it_Objet->obtMasse() != 0) {
						if (it_Objet->obtModele3D()->obtPosition().x >= it->obtPosition().x && it_Objet->obtModele3D()->obtPosition().x <= it->obtPosition().x + it_Vent->obtDimensions().x) {
							if (it_Objet->obtModele3D()->obtPosition().y >= it->obtPosition().y && it_Objet->obtModele3D()->obtPosition().y <= it->obtPosition().y + it_Vent->obtDimensions().y) {
								if (it_Objet->obtModele3D()->obtPosition().z >= it->obtPosition().z && it_Objet->obtModele3D()->obtPosition().z <= it->obtPosition().z + it_Vent->obtDimensions().z) {
									Physique::obtInstance().appliquerVent(it->obtVitesse(), *it_Objet, frameTime);
								}
							}
						}
					}
				}
			}
			Aimant* it_Aimant = dynamic_cast<Aimant*>(it);
			if (it_Aimant != nullptr) {
				for (auto it_Objet : objets) {
					if (it_Objet->obtMasse() != 0) {
						appliquerMagnetisme(*it_Objet, it_Aimant->obtPosition(), it_Aimant->obtForce(), frameTime);
					}
				}
			}
			Pendule* it_Pendule = dynamic_cast<Pendule*>(it);
			if (it_Pendule != nullptr) {
				double angle = obtenirAnglePenduleSimple(it_Pendule->obtAngleMax(), it_Pendule->obtVitesseAngulaire().norme(), it_Pendule->obtConstantePhase(), temps);
				Vecteur3d vectemp = it_Pendule->obtVitesseAngulaire() * angle;
				vectemp.y = it_Pendule->obtModele3D()->obtOrientation().y;
				it_Pendule->obtModele3D()->defOrientation(vectemp);
			}
			ObjetFixe* it_ObjetFixe = dynamic_cast<ObjetFixe*>(it);
			if (it_ObjetFixe != nullptr) {
				for (auto it_Objet : objets) {
					if (it_Objet->obtMasse() != 0) {

					}
				}
			}
			ObjetPhysique* it_ObjetPhysique = dynamic_cast<ObjetPhysique*>(it);
			if (it_ObjetPhysique != nullptr) {
				if (it->obtVitesse().norme() > 0 && !collisionObjetSalle(modeleSalle, objets, *it)) {
					appliquerGravite(it->obtVitesse(), frameTime);
					it->defPosition(it->obtPosition() + it->obtVitesse() * frameTime);
				}
			}
		}
	}

	void rebondObjetCarte(Objet& objet, Vecteur3d vecteurNormal, Vecteur3d pointdecollision) {

		Vecteur3d* BoiteDeCollisionModifiee = objet.obtModele3D()->obtBoiteDeCollisionModifiee();

		Vecteur3d positionCM = { 0, 0, 0 };

		for (unsigned int i = 0; i < 8; i++) {
			positionCM.x += BoiteDeCollisionModifiee[i].x;
		}
		for (unsigned int i = 0; i < 8; i++) {
			positionCM.y += BoiteDeCollisionModifiee[i].y;
		}
		for (unsigned int i = 0; i < 8; i++) {
			positionCM.z += BoiteDeCollisionModifiee[i].z;
		}
		positionCM /= 8;

		Vecteur3d rayon = { positionCM.x - pointdecollision.x, positionCM.y - pointdecollision.y, positionCM.z - pointdecollision.z };

		Vecteur3d axederotation = rayon.produitVectoriel(vecteurNormal);
		axederotation.normaliser();

		if (axederotation.norme() != 0) {

			double cr = 1 - mapRestitution[objet.obtMateriaux()];
			double r = rayon.norme();
			double theta = sin(vecteurNormal.angleEntreVecteurs(rayon));
			double masse = objet.obtMasse();
			double vi = objet.obtVitesse().norme();
				//double wi = objet.obtVitesseAngulaire().norme();

			// Pour le calcul du moment d'inertie...
			Vecteur3d  coteX = { BoiteDeCollisionModifiee[7].x - BoiteDeCollisionModifiee[4].x,
				BoiteDeCollisionModifiee[7].y - BoiteDeCollisionModifiee[4].y,
				BoiteDeCollisionModifiee[7].z - BoiteDeCollisionModifiee[4].z };
			double longueurcoteX = coteX.norme();
			coteX.normaliser();

			Vecteur3d coteY = { BoiteDeCollisionModifiee[5].x - BoiteDeCollisionModifiee[4].x,
				BoiteDeCollisionModifiee[5].y - BoiteDeCollisionModifiee[4].y,
				BoiteDeCollisionModifiee[5].z - BoiteDeCollisionModifiee[4].z };
			double longueurcoteY = coteY.norme();
			coteY.normaliser();

			Vecteur3d coteZ = { BoiteDeCollisionModifiee[0].x - BoiteDeCollisionModifiee[4].x,
				BoiteDeCollisionModifiee[0].y - BoiteDeCollisionModifiee[4].y,
				BoiteDeCollisionModifiee[0].z - BoiteDeCollisionModifiee[4].z };
			double longueurcoteZ = coteZ.norme();
			coteZ.normaliser();

			double I = calculerMomentInertie(axederotation, coteX, coteY, coteZ, longueurcoteX, longueurcoteY, longueurcoteZ, masse);
			double r2theta2 = pow(r, 2)*pow(theta, 2);
			double masser2theta2 = masse*r2theta2;
			double a = (masse / 2)*(1 + (masser2theta2) / (I));
			double b = (-pow(masse, 2)*r2theta2*vi) / I;
			double c = (masse*pow(vi, 2) / 2) * (((masser2theta2) / (I)) - (pow(cr, 2)));

			double vitesseFinale = (-b - sqrt(pow(b, 2) - 4 * a*c)) / (2 * a);

			double wf = (r * masse * (vitesseFinale - vi) * theta) / I * 20;

			Vecteur3d vvitesseAngulaire = axederotation * wf;

			objet.defVitesseAngulaire(vvitesseAngulaire);
			objet.obtVitesse().normaliser();
			double dScalaire = (2 - mapRestitution[objet.obtMateriaux()]) * objet.obtVitesse().produitScalaire(vecteurNormal);
			objet.obtVitesse() -= vecteurNormal * dScalaire;
			objet.obtVitesse() *= vitesseFinale;
		}
		else
		{
			// Rebond simple sans rotation...
			double dScalaire = (2 - mapRestitution[objet.obtMateriaux()]) * objet.obtVitesse().produitScalaire(vecteurNormal);
			objet.obtVitesse() -= vecteurNormal * dScalaire;
		}
	}

	// Procédure qui donne le moment d'inertie d'un rectangle, tous les vecteurs doivent être normalisés(unitaires).
	double calculerMomentInertie(Vecteur3d axederotation, Vecteur3d coteX, Vecteur3d coteY, Vecteur3d coteZ, double longueurcoteX, double longueurcoteY, double longueurcoteZ, double masse) {

		double dcoteX = abs(coteX.produitScalaire(axederotation));
		double dcoteY = abs(coteY.produitScalaire(axederotation));
		double dcoteZ = abs(coteZ.produitScalaire(axederotation));

		if (dcoteX > dcoteY && dcoteX > dcoteZ) {
			return (masse * (pow(longueurcoteY, 2) + pow(longueurcoteZ, 2))) / 12;
		}
		if (dcoteY > dcoteX && dcoteY > dcoteZ) {
			return (masse * (pow(longueurcoteX, 2) + pow(longueurcoteZ, 2))) / 12;
		}
		if (dcoteZ > dcoteX && dcoteZ > dcoteY) {
			return (masse * (pow(longueurcoteX, 2) + pow(longueurcoteY, 2))) / 12;
		}
		return NULL;
	}

	void rebondObjetObjet(Objet& objet1, Objet& objet2, Vecteur3d vecteurNormal) {

		Vecteur3d vVitesseRelative = objet1.obtVitesse() - objet2.obtVitesse();

		double e = (mapRestitution[objet1.obtMateriaux()] + mapRestitution[objet2.obtMateriaux()]) / 2; // Moyenne des coefficients de restitution

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

	void appliquerGravite(Vecteur3d &vecteurVitesseObjet, double frametime) {
		vecteurVitesseObjet.y += gravite * frametime;
	}

	void appliquerVent(Vecteur3d vecteurVitesseVent, Objet& objet, double frametime) {

		double* tableaunormale = objet.obtModele3D()->obtNormalesModifies(); //À MODIFIER LORSQUE LES MODIF DE normale FONCTIONNENT!
		double* tableauVertices = objet.obtModele3D()->obtSommetsModifies();

		double accelerationSelonForceVent = 0.5 * 1.204 * pow(vecteurVitesseVent.norme(), 2);

		double coefficientTrainer = 0;
		double surface = 0;

		double nombreVertice = objet.obtModele3D()->obtModele()->obtNbrVertices();

		unsigned int nombreFaceSousPression = 0;

		// Boucle sur toutes les faces de l'objet
		for (unsigned int parcoursFace = 0; parcoursFace < nombreVertice;) {

			// Vecteur normal de la face selon une moyenne de ceux des vertices.
			Vecteur3d vecteurNormale = { (tableaunormale[parcoursFace] + tableaunormale[parcoursFace + 3] + tableaunormale[parcoursFace + 6]) / 3,
				(tableaunormale[parcoursFace + 1] + tableaunormale[parcoursFace + 4] + tableaunormale[parcoursFace + 7]) / 3,
				(tableaunormale[parcoursFace + 2] + tableaunormale[parcoursFace + 5] + tableaunormale[parcoursFace + 8]) / 3 };

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

	void appliquerFrottement(Objet& objet, Vecteur3d& normale) {
		objet.obtVitesse().soustraire(constanteDeFriction * obtenirForceNormale(objet.obtMasse(), objet.obtPosition(), normale));
	}

	// Procédure qui applique la force d'attraction magnétique sur un objet
	// (La force du champs et la sensibilité magnétique de l'objet sont constant).
	void appliquerMagnetisme(Objet& objet, Vecteur3d positionAimant, double force, double frametime) {

		double distanceObjetAimant = Maths::distanceEntreDeuxPoints(positionAimant, objet.obtPosition());
		double accelerationMagnetique = (6 * sensibiliteMagnetique * force) / (objet.obtMasse() * distanceObjetAimant);

		Vecteur3d vecteurProportionnel = { positionAimant.x - objet.obtPosition().x, positionAimant.y - objet.obtPosition().y, positionAimant.z - objet.obtPosition().z };
		vecteurProportionnel.normaliser();

		Vecteur3d vecteurAcceleration = { accelerationMagnetique, accelerationMagnetique, accelerationMagnetique };

		vecteurAcceleration.produitParUnVecteur(vecteurProportionnel);

		objet.obtVitesse() += vecteurAcceleration * frametime;

	}

	double obtenirAnglePenduleSimple(double angleMaximal, double omega, double phase, double frametime) {
		return Maths::radianADegre(Maths::degreARadian(angleMaximal) * SDL_cos(omega * frametime + phase));
	}

	double obtenirEnergieCinetique(double masse, Vecteur3d& vecteurVitesseObjet) {
		return 0.5 * masse * SDL_pow(vecteurVitesseObjet.norme(), 2);
	}

	bool collisionObjetSalle(gfx::Modele3D* modeleSalle, std::list<Objet*> listeObjet, Objet& objet) {
		Droite rayonCollision;
		Vecteur3d pointCollision;
		Vecteur3d point;
		Vecteur3d normale;
		Vecteur3d difference;
		Vecteur3d* tabObjet = objet.obtModele3D()->obtBoiteDeCollisionModifiee();
		ObjetPhysique* it_physique;

		for (int i = 0; i < 8; i++) {

			point = tabObjet[i];
			rayonCollision = Droite(point, objet.obtVitesse());

			if (collisionDroiteModele(modeleSalle, rayonCollision, pointCollision, normale, nullptr)) {

				difference = pointCollision - point;
				objet.defPosition(objet.obtPosition() + difference);

				normale.normaliser();
				rebondObjetCarte(objet, normale, pointCollision);


				return true;
			}

			for (auto it : listeObjet) {

				if (it->obtID() != objet.obtID()) {

					if (collisionDroiteObjet(*it, rayonCollision, pointCollision, normale)) {

						it_physique = dynamic_cast<ObjetPhysique*>(it);

						if (it_physique)
							rebondObjetObjet(objet, *it, normale);
						else
							rebondObjetCarte(objet, normale, pointCollision);

						collision = true;
						return true;
					}
				}
			}
		}
		return false;
	}

	short collisionJoueurSalle(gfx::Modele3D* modeleSalle, Vecteur3d* bteCollision, Vecteur3d& vitesseJoueur, Vecteur3d&normaleJoueur, Vecteur3d&normaleMur, Vecteur3d& pointCollisionJoueur, Vecteur3d& positionJoueur, Vecteur3d* verticesCollision) {
		Droite rayonCollision;
		Vecteur3d pointCollision;
		Vecteur3d point;
		Vecteur3d normale;
		float hauteur;
		short collision = AUCUNE;

		for (int i = 0; i < 8; i++) {

			point = bteCollision[i];

			rayonCollision = Droite(point, vitesseJoueur);
			bool mur = false;
			if (collisionDroiteModele(modeleSalle, rayonCollision, pointCollision, normale, verticesCollision)) {
				if (fabs(normale.x) < 0.05f)
					normale.x = 0.f;
				if (fabs(normale.z) < 0.05f)
					normale.z = 0.f;
				normale.normaliser();
				normaleJoueur = (normale);
				pointCollisionJoueur = (pointCollision);
				if (normale.y == 1)
					collision = SOLDROIT;
				if (normale.y > fabs(normale.x) && normale.y > fabs(normale.z))
					collision = SOLCROCHE;
				if (normale.y == 0){
					normaleMur = (normale);
					collision = MUR;
					mur = true;
				}
				else {
					if (!mur && i == 7)
						normaleMur = Vecteur3d(0.f, 1.f, 0.f);
				}

				if (collision != MUR) {
					Vecteur3d pointDifference = pointCollision - point;
					positionJoueur.y += pointDifference.y;
				}
				else{
					Vecteur3d pointDifference = pointCollision - point;
						positionJoueur = Vecteur3d(positionJoueur.x + pointDifference.x, positionJoueur.y, positionJoueur.z + pointDifference.z);
				}
			}
		}
		if (collision == AUCUNE) {
			normaleJoueur = Vecteur3d({ 0, 0, 0 });
		}

		return collision;
	}

	bool collisionJoueurObjet(Objet &objet, Vecteur3d* bteCollision, Vecteur3d& vitesseJoueur, Vecteur3d& positionJoueur) {
		Droite rayonCollision;
		Vecteur3d pointCollision;
		Vecteur3d point;
		Vecteur3d normale;

		for (int i = 0; i < 8; i++) {
			point = bteCollision[i];

			rayonCollision = Droite(point, vitesseJoueur);

			if (collisionDroiteObjet(objet, rayonCollision, pointCollision, normale)) {
				Vecteur3d pointDiference = pointCollision - point;
				positionJoueur += pointDiference;
				return true;
			}
		}
		return false;
	}

};
