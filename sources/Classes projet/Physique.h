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
#include "Remplisseur.h"
#include "PlafondTueur.h"
#include <string>

enum collisions{ AUCUNE, MUR, SOLDROIT, SOLCROCHE, PLAFOND };

class Physique : public Singleton < Physique > {
private:

	double gravite;
	double constanteDeFriction;
	double sensibiliteMagnetique;
	std::map<char*, double> mapRestitution;
	bool collision;

	bool collisionDroiteObjet(Objet& objet, Droite& rayonCollision, Vecteur3d& pointCollision, Vecteur3d& normale) {

		Vecteur3d point1;
		Vecteur3d point2;
		Vecteur3d point3;
		Vecteur3d point;
		Vecteur3d* boiteCollision = objet.obtModele3D()->obtBoiteDeCollisionModifiee();
		Plan plan;
		Vecteur3i* indices = objet.obtModele3D()->obtModele()->obtIndidesBoiteDeCollision();
		Vecteur3f* normales = objet.obtModele3D()->obtModele()->obtNormalesBoiteDeCollision();

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
		mapRestitution["plastique"] = 0.68;
		mapRestitution["ballerebondissante"] = 0.1;
		mapRestitution["carton"] = 0.55;
	}

	bool collisionDroiteModele(gfx::Modele3D* modele3D, Droite& rayonCollision, Vecteur3d& pointCollision, Vecteur3d& normale, Vecteur3d* verticesCollision, bool collisionReelle) {

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
					if (collisionReelle){
						point = pointCollision + rayonCollision.obtenirVecteurDirecteur();
						if (Maths::memeCote(point, rayonCollision.obtenirPoint(), pointCollision, point1)) {
							normale.normaliser();
							rayonCollision.obtenirVecteurDirecteur().normaliser();
							scalaire = normale.produitScalaire(rayonCollision.obtenirVecteurDirecteur());
							if (scalaire < 0 && (Maths::distanceEntreDeuxPoints(pointCollision, rayonCollision.obtenirPoint()) < 1))
								return true;
						}
					}
					else{
						scalaire = normale.produitScalaire(rayonCollision.obtenirVecteurDirecteur());
						if (scalaire < 0)
							return true;
					}



				}
			}
		}
		return false;
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
									appliquerForceVent(it_Objet, it->obtVitesse());
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
						appliquerForceMagnetique(it_Objet, it_Aimant);
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
			PlafondTueur* it_Plafond = dynamic_cast<PlafondTueur*>(it);
			if (it_Plafond){
				Vecteur3d plafPos = it_Plafond->obtPosition();
				plafPos.y = cos(temps) + 2;
				it_Plafond->defPosition(plafPos);
			}
			ObjetPhysique* it_ObjetPhysique = dynamic_cast<ObjetPhysique*>(it);
			if (it_ObjetPhysique != nullptr) {
				//if (!it_ObjetPhysique->estStable()) {
				appliquerForceGravite(it_ObjetPhysique);
				if (it->obtVitesse().norme() > 0 && !collisionObjetSalle(modeleSalle, objets, *it, frameTime)) {

					it->obtVitesse() += it->obtForceTotale() * (frameTime / it->obtMasse());

					it->defPosition(it->obtPosition() + it->obtVitesse() * frameTime);
					it->obtModele3D()->defOrientation(it->obtModele3D()->obtOrientation() - (it->obtVitesseAngulaire() * 180 * frameTime / M_PI));
					it->obtForceTotale() = { 0, 0, 0 };
				}
				else
				{
					it->obtVitesse() += it->obtForceTotale() * (frameTime / it->obtMasse());
					it->defPosition(it->obtPosition() + it->obtVitesse() * frameTime);
					it->obtModele3D()->defOrientation(it->obtModele3D()->obtOrientation() - (it->obtVitesseAngulaire() * 180 * frameTime / M_PI));
				}
				//}
			}
		}
	}

	/*void appliquerSurJoueur(gfx::Modele3D* modeleJoeur, Vecteur3d& vitesseJoueur, Objet* objet, float frameTime, double temps){
		Vent* it_Vent = dynamic_cast<Vent*>(objet);
		appliquerVent(it_Vent->obtVitesse(), vitesseJoueur, modeleJoeur, 87, frameTime);
		Pendule* it_Pendule = dynamic_cast<Pendule*>(objet);
		if (it_Pendule != nullptr) {
		}
	}*/

	void rebondObjetCarte(Objet& objet, Vecteur3d normale, Vecteur3d pointdeCollision, double frameTime) {

		for (unsigned int i = 0; i < 6; ++i) {
			Vecteur3f huehue = objet.obtModele3D()->obtNormaleBoiteDeCollision()[i];
			huehue.normaliser();
			float f = huehue.produitScalaire(Vecteur3f(normale.x, normale.y, normale.z));
			if (f > 0.99) {
				objet.defStable(true);
			}
		}

		if (!objet.estStable()) {

			BoiteCollision<double> BoiteDeCollision = objet.obtModele3D()->obtBoiteCollision();

			Vecteur3d positionCentre = BoiteDeCollision.obtCentreBoite();
			Vecteur3d rayon = Maths::vecteurEntreDeuxPoints(pointdeCollision, BoiteDeCollision.obtCentreBoite());

			normale.normaliser();

			double theta = (normale).angleEntreVecteurs(Vecteur3d(0, -1, 0));

			Vecteur3d ForceNormale = normale * (objet.obtMasse() * -9.8 * cos(theta));

			Vecteur3d tau = rayon.produitVectoriel(ForceNormale);

			// Pour le calcul du moment d'inertie...
			Vecteur3d coteX = Maths::vecteurEntreDeuxPoints(BoiteDeCollision.obtBoite()[4], BoiteDeCollision.obtBoite()[7]);
			double longueurcoteX = coteX.norme();
			coteX.normaliser();

			Vecteur3d coteY = Maths::vecteurEntreDeuxPoints(BoiteDeCollision.obtBoite()[4], BoiteDeCollision.obtBoite()[5]);
			double longueurcoteY = coteY.norme();
			coteY.normaliser();

			Vecteur3d coteZ = Maths::vecteurEntreDeuxPoints(BoiteDeCollision.obtBoite()[4], BoiteDeCollision.obtBoite()[0]);
			double longueurcoteZ = coteZ.norme();
			coteZ.normaliser();

			double I = calculerMomentInertie(tau, coteX, coteY, coteZ, longueurcoteX, longueurcoteY, longueurcoteZ, objet.obtMasse());

			objet.defVitesseAngulaire(objet.obtVitesseAngulaire() + (tau * (frameTime / I)));

			//if (!objet.estEnCollision()) {

			//	// Patching de conservation d'énergie....
			//	/*theta = rayon.angleEntreVecteurs(vecteurNormal);
			//	double vi = objet.obtVitesse().produitScalaire(vecteurNormal);
			//	double dScalaire = (2 - mapRestitution[objet.obtMateriaux()]) * objet.obtVitesse().produitScalaire(vecteurNormal);
			//	objet.obtVitesse() -= vecteurNormal * dScalaire;
			//	double r = rayon.norme();
			//	double masse = objet.obtMasse();
			//	double vf = objet.obtVitesse().produitScalaire(vecteurNormal);
			//	tau.normaliser();
			//	Vecteur3d ttttt = tau * (r * masse * (vf - vi) * sin(theta) / I);
			//	objet.defVitesseAngulaire(objet.obtVitesseAngulaire() + (tau * (r * masse * (vf - vi) * sin(theta) * 0.1 / I)));*/

			//	//// Variables utiles....
			//	//theta = rayon.angleEntreVecteurs(vecteurNormal);
			//	//double r = rayon.norme();
			//	//double masse = objet.obtMasse();
			//	//double vi = objet.obtVitesse().produitScalaire(vecteurNormal);
			//	//double wi = objet.obtVitesseAngulaire().norme();
			//	//double Ei = 2 * (pow(1 - mapRestitution[objet.obtMateriaux()], 2)) * ((0.5 * masse * pow(vi, 2)) + (0.5 * I * pow(wi, 2)));

			//	//// Grosse Berta....
			//	//double a = masse + (pow((r * masse * sin(theta)), 2) / I);
			//	//double b = (2 * r*masse*sin(theta)*wi) - ((2 * vi*pow((r*masse*sin(theta)), 2)) / I);
			//	//double c = (I * pow(wi, 2)) - (2 * r*masse*sin(theta)*vi*wi) + (pow((r*masse*sin(theta)*vi), 2) / I) - Ei;

			//	//double vf = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
			//	//
			//	//if ((pow(b, 2) - 4 * a * c) > 0) {
			//	//	objet.defVitesse(objet.obtVitesse() - (vecteurNormal * vi) + (vecteurNormal * vf));
			//	//	tau.normaliser();
			//	//	objet.defVitesseAngulaire(objet.obtVitesseAngulaire() + (tau * (r * masse * (vf - vi) * sin(theta) / I)));
			//	//}
			//	//else
			//	//{
			//	//	double dScalaire = (2 - mapRestitution[objet.obtMateriaux()]) * objet.obtVitesse().produitScalaire(vecteurNormal);
			//	//	objet.obtVitesse() -= vecteurNormal * dScalaire * 1.5;
			//	//}
			//}
			//else
			//{
			//	objet.defVitesse(Vecteur3d(0, 0, 0));
			//}
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

		objet1.defStable(false);
		objet2.defStable(false);
	}

	void appliquerForceNormale(Objet* objet, Vecteur3d normale) {

		objet->obtForceTotale() += normale * (objet->obtMasse() * -9.8 * cos((normale).angleEntreVecteurs(Vecteur3d(0, -1, 0))));
	}

	void appliquerForceGravite(Objet* objet) {
		objet->obtForceTotale() += Vecteur3d(0, -1, 0) * (objet->obtMasse() * 9.8);
	}

	void appliquerGravite(Vecteur3d &vecteurVitesseObjet, double frametime) {
		vecteurVitesseObjet.y += gravite * frametime;
	}

	void appliquerForceVent(Objet* objet, Vecteur3d vitesseVent) {

		double* tableaunormale = objet->obtModele3D()->obtNormalesModifies();
		double* tableauVertices = objet->obtModele3D()->obtSommetsModifies();

		Vecteur3d ForceVent;

		double coefficientTrainer = 0;
		double surface = 0;

		double nombreVertice = objet->obtModele3D()->obtModele()->obtNbrVertices();

		unsigned int nombreFaceSousPression = 0;

		// Boucle sur toutes les faces de l'objet
		for (unsigned int parcoursFace = 0; parcoursFace < nombreVertice;) {

			// Vecteur normal de la face selon une moyenne de ceux des vertices.
			Vecteur3d vecteurNormale = { (tableaunormale[parcoursFace] + tableaunormale[parcoursFace + 3] + tableaunormale[parcoursFace + 6]) / 3,
				(tableaunormale[parcoursFace + 1] + tableaunormale[parcoursFace + 4] + tableaunormale[parcoursFace + 7]) / 3,
				(tableaunormale[parcoursFace + 2] + tableaunormale[parcoursFace + 5] + tableaunormale[parcoursFace + 8]) / 3 };

			double angleEntreVecteursVentNormale = (vitesseVent.produitScalaire(vecteurNormale)) / (vitesseVent.norme() * vecteurNormale.norme());

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

		vitesseVent.normaliser();

		objet->obtForceTotale() += vitesseVent * (0.5 * coefficientTrainer * 1.293 * pow(vitesseVent.norme(), 2) * surface);
	}

	void appliquerForceFrottement(Objet* objet, Vecteur3d normale) {

		objet->obtForceTotale() += (objet->obtVitesse().produitVectoriel(normale)).produitVectoriel(normale) * (constanteDeFriction * objet->obtMasse() * -9.8 * cos((normale).angleEntreVecteurs(Vecteur3d(0, -1, 0))));
	}

	// Procédure qui applique la force d'attraction magnétique sur un objet
	// (La force du champs et la sensibilité magnétique de l'objet sont constant).
	void appliquerForceMagnetique(Objet* objet, Aimant* aimant) {

		objet->obtForceTotale() += Maths::vecteurEntreDeuxPoints(objet->obtPosition(), aimant->obtPosition()) * ((6 * sensibiliteMagnetique * aimant->obtForce()) / objet->obtMasse());
	}

	double obtenirAnglePenduleSimple(double angleMaximal, double omega, double phase, double frametime) {
		return Maths::radianADegre(Maths::degreARadian(angleMaximal) * SDL_cos(omega * frametime + phase));
	}

	double obtenirEnergieCinetique(double masse, Vecteur3d& vecteurVitesseObjet) {
		return 0.5 * masse * SDL_pow(vecteurVitesseObjet.norme(), 2);
	}

	bool collisionObjetSalle(gfx::Modele3D* modeleSalle, std::list<Objet*> listeObjet, Objet& objet, double frameTime) {

		Droite rayonCollision;
		Vecteur3d pointCollision;
		Vecteur3d point;
		Vecteur3d normale;
		Vecteur3d difference;
		Vecteur3d* tabObjet = objet.obtModele3D()->obtBoiteDeCollisionModifiee();
		Vecteur3d pointDeCollision;
		Vecteur3d normaleDeCollision;
		unsigned int nbrCollision = 0;

		ObjetPhysique* it_physique;

		for (int i = 0; i < 8; i++) {

			point = tabObjet[i];
			rayonCollision = Droite(point, objet.obtVitesse());

			if (collisionDroiteModele(modeleSalle, rayonCollision, pointCollision, normale, nullptr, true)) {

				difference = pointCollision - point;
				objet.defPosition(objet.obtPosition() + difference);

				++nbrCollision;

				pointDeCollision += pointCollision;
				normaleDeCollision += normale;
			}

			for (auto it : listeObjet) {

				if (it->obtID() != objet.obtID()) {

					if (collisionDroiteObjet(*it, rayonCollision, pointCollision, normale)) {

						it_physique = dynamic_cast<ObjetPhysique*>(it);

						if (it_physique) {

							rebondObjetObjet(objet, *it, normale);
							return true;
						}
						else {

							++nbrCollision;
							pointDeCollision += pointCollision;
							normaleDeCollision += normale;
						}
					}
				}
			}
		}

		if (nbrCollision != 0) {

			pointDeCollision /= nbrCollision;
			normaleDeCollision /= nbrCollision;
			normale.normaliser();
			rebondObjetCarte(objet, normaleDeCollision, pointDeCollision, frameTime);
			appliquerForceNormale(&objet, normaleDeCollision);
			appliquerForceFrottement(&objet, normaleDeCollision);
			return true;
		}

		return false;
	}

	bool collisionJoueurSalle(gfx::Modele3D* modeleSalle, Joueur* joueur) {
		Droite rayonCollision;
		Droite collisionEscalier;
		Vecteur3d pointCollision;
		Vecteur3d point;
		Vecteur3d normale;
		Vecteur3d* tabJoueur = joueur->obtModele3D()->obtBoiteDeCollisionModifiee();
		Vecteur3d verticesCollision[3];
		collisions typeCollision = AUCUNE;
		bool mur = false;
		bool escalier = false;

		for (int i = 0; i < 8; i++) {
			point = tabJoueur[i];
			rayonCollision = Droite(point, joueur->obtVitesse());
			if (joueur->obtVitesse().y < 0.f)
				rayonCollision.obtenirVecteurDirecteur().y = 0;

			if (collisionDroiteModele(modeleSalle, rayonCollision, pointCollision, normale, nullptr, true)) {
				if (fabs(normale.x) < 0.05f)
					normale.x = 0.f;
				if (fabs(normale.z) < 0.05f)
					normale.z = 0.f;
				normale.normaliser();
				joueur->defNormale(normale);
				joueur->defPointCollision(pointCollision);

				// Collision au Plafond
				if (normale.y < 0){
					joueur->obtVitesse().y = -0.000000000001f;
					joueur->defEtat(CHUTE);
					Vecteur3d pointDifference = pointCollision - point;
					joueur->defPosition(Vecteur3d(joueur->obtPosition().x + pointDifference.x, joueur->obtPosition().y, joueur->obtPosition().z + pointDifference.z));
					return true;
				}

				// Collision sur un mur
				if (normale.y == 0) {
					if (point.y < joueur->obtPosition().y + 1) {
						collisionEscalier = Droite(Vecteur3d(point.x, point.y + 0.5, point.z), joueur->obtVitesse());
						if (!collisionDroiteModele(modeleSalle, collisionEscalier, pointCollision, normale, verticesCollision, true)) {
							double hauteur = 0.f;
							if (verticesCollision[0].x == verticesCollision[1].x && verticesCollision[0].z == verticesCollision[1].z)
								hauteur = fabs(verticesCollision[0].y - verticesCollision[1].y);
							if (verticesCollision[0].x == verticesCollision[2].x && verticesCollision[0].z == verticesCollision[2].z)
								hauteur = fabs(verticesCollision[0].y - verticesCollision[2].y);
							if (verticesCollision[1].x == verticesCollision[2].x && verticesCollision[1].z == verticesCollision[2].z)
								hauteur = fabs(verticesCollision[1].y - verticesCollision[2].y);
							if (hauteur != 0.f)
								joueur->defPositionY(joueur->obtPosition().y + hauteur + .03);
							escalier = true;
						}
					}
					joueur->defNormaleMur(normale);
					typeCollision = MUR;
					mur = true;
					if (!escalier) {
						Vecteur3d pointDifference = pointCollision - point;
						if (pointDifference.y != 0)
							pointDifference.y = 0;
						double normePointDifference = pointDifference.norme();
						Vecteur3d normaleReposition = normale;
						normaleReposition *= normePointDifference;
						joueur->defPosition(Vecteur3d(joueur->obtPosition().x + normaleReposition.x, joueur->obtPosition().y, joueur->obtPosition().z + normaleReposition.z));
					}
				}
				joueur->obtVitesse().x = 0.;
				joueur->obtVitesse().z = 0.;
			}
		}


		for (int i = 0; i < 8; i++) {
			point = tabJoueur[i];
			rayonCollision = Droite(point, { 0, -9.8, 0 });

			if (collisionDroiteModele(modeleSalle, rayonCollision, pointCollision, normale, nullptr, true)) {
				normale.normaliser();
				joueur->defNormale(normale);
				joueur->defPointCollision(pointCollision);
				if (normale.y == 1) {
					typeCollision = SOLDROIT;
				}
				if (normale.y != 0.f && (normale.x != 0.f || normale.z != 0.f))
					typeCollision = SOLCROCHE;

				if (typeCollision != MUR) {
					if (joueur->obtVitesse().y <= -12 && joueur->obtVitesse().y >= -35) {
						joueur->defSantePhysique(joueur->obtSantePhysique() - fabs(joueur->obtVitesse().y * 0.5));
					}
					if (joueur->obtVitesse().y < -35)
						joueur->defSantePhysique(0);
					Vecteur3d pointDifference = pointCollision - point;
					joueur->defPositionY(joueur->obtPosition().y + pointDifference.y);
				}
				else{
					if (!escalier) {
						Vecteur3d pointDifference = pointCollision - point;
						joueur->defPosition(Vecteur3d(joueur->obtPosition().x + pointDifference.x, joueur->obtPosition().y, joueur->obtPosition().z + pointDifference.z));
					}
				}
				if ((typeCollision == SOLDROIT || typeCollision == SOLCROCHE)){
					joueur->obtVitesse().y = 0.f;
					joueur->defEtat(STABLE);
				}
				return typeCollision;
			}
		}
		if (typeCollision == AUCUNE) {
			joueur->defEtat(CHUTE);
			joueur->defNormale({ 0, 0, 0 });
		}
		return typeCollision;
	}

	bool collisionJoueurObjet(Joueur* joueur, std::list<Objet*> listeObjet) {
		Droite rayonCollision;
		Vecteur3d pointCollision;
		Vecteur3d point;
		Vecteur3d normale;
		Vecteur3d difference;
		Vecteur3d* tabJoueur;
		collisions typeCollision = AUCUNE;
		bool mur = false;

		for (auto it : listeObjet) {
			if (!it->obtCollisionInterne()) {
				for (unsigned int i = 0; i < (joueur->obtModele3D()->obtModele()->obtNbrVertices() / 3); i++) {
					for (unsigned int j = 0; j < 3; j++) {
						if (j == 0)
							point.x = joueur->obtModele3D()->obtSommetsModifies()[i * 3 + j];
						else if (j == 1)
							point.y = joueur->obtModele3D()->obtSommetsModifies()[i * 3 + j];
						else if (j == 2)
							point.z = joueur->obtModele3D()->obtSommetsModifies()[i * 3 + j];
					}
					rayonCollision = Droite(point, joueur->obtVitesse());
					if (it->obtModele3D()->obtBoiteCollision().pointDansBoite(point, rayonCollision, normale, joueur->obtVitesse(), pointCollision)) {
						if (fabs(normale.x) < 0.05f)
							normale.x = 0.f;
						if (fabs(normale.z) < 0.05f)
							normale.z = 0.f;
						normale.normaliser();
						joueur->defNormale(normale);
						joueur->defPointCollision(pointCollision);

						// Collision au Plafond
						if (normale.y < 0){
							joueur->obtVitesse().y = -0.000000000001f;
							joueur->defEtat(CHUTE);
							Vecteur3d pointDifference = pointCollision - point;
							joueur->defPosition(Vecteur3d(joueur->obtPosition().x + pointDifference.x, joueur->obtPosition().y, joueur->obtPosition().z + pointDifference.z));
							return true;
						}

						// Collision sur un mur
						if (normale.y == 0) {
							joueur->defNormaleMur(normale);
							typeCollision = MUR;
							mur = true;
							Vecteur3d pointDifference = pointCollision - point;
							joueur->defPosition(Vecteur3d(joueur->obtPosition().x + pointDifference.x, joueur->obtPosition().y, joueur->obtPosition().z + pointDifference.z));
						}
						joueur->obtVitesse().x = 0.;
						joueur->obtVitesse().z = 0.;
						break;
					}
				}

				for (unsigned int i = 0; i < (joueur->obtModele3D()->obtModele()->obtNbrVertices() / 3); i++) {
					for (unsigned int j = 0; j < 3; j++) {
						if (j == 0)
							point.x = joueur->obtModele3D()->obtSommetsModifies()[i * 3 + j];
						else if (j == 1)
							point.y = joueur->obtModele3D()->obtSommetsModifies()[i * 3 + j];
						else if (j == 2)
							point.z = joueur->obtModele3D()->obtSommetsModifies()[i * 3 + j];
					}
					rayonCollision = Droite(point, joueur->obtVitesse());
					if (it->obtModele3D()->obtBoiteCollision().pointDansBoite(point, rayonCollision, normale, joueur->obtVitesse(), pointCollision)) {
						if (fabs(normale.x) < 0.05f)
							normale.x = 0.f;
						if (fabs(normale.z) < 0.05f)
							normale.z = 0.f;
						normale.normaliser();
						joueur->defNormale(normale);
						joueur->defPointCollision(pointCollision);
						if (normale.y == 1) {
							typeCollision = SOLDROIT;
						}
						if (normale.y != 0.f && (normale.x != 0.f || normale.z != 0.f))
							typeCollision = SOLCROCHE;

						if (typeCollision != MUR) {
							if (joueur->obtVitesse().y <= -12 && joueur->obtVitesse().y >= -35) {
								joueur->defSantePhysique(joueur->obtSantePhysique() - fabs(joueur->obtVitesse().y * 0.5));
							}
							if (joueur->obtVitesse().y < -35)
								joueur->defSantePhysique(0);
							Vecteur3d pointDifference = pointCollision - point;
							joueur->defPositionY(joueur->obtPosition().y + pointDifference.y);
						}
						if ((typeCollision == SOLDROIT || typeCollision == SOLCROCHE)){
							joueur->obtVitesse().y = 0.f;
							joueur->defEtat(STABLE);
						}
						return typeCollision;
					}
				}
			}
			if (it->obtCollisionInterne() || dynamic_cast<Remplisseur*>(it)) {
				/*collisionJoueurSalle(it->obtModele3D(), joueur);*/
				return true;
			}
		}
		return false;
	}

};