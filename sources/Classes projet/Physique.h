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
		mapRestitution["metal"] = 0.6;
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
									Physique::obtInstance().appliquerVent(it->obtVitesse(), (*it_Objet).obtVitesse(), (*it_Objet).obtModele3D(), it->obtMasse(), frameTime);
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

	void appliquerSurJoueur(gfx::Modele3D* modeleJoeur, Vecteur3d& vitesseJoueur, Objet* objet, float frameTime, double temps){
		Vent* it_Vent = dynamic_cast<Vent*>(objet);
		appliquerVent(it_Vent->obtVitesse(), vitesseJoueur, modeleJoeur, 87, frameTime);
		Pendule* it_Pendule = dynamic_cast<Pendule*>(objet);
		if (it_Pendule != nullptr) {
		}
	}

	void rebondObjetCarte(Objet& objet, Vecteur3d vecteurNormal, Vecteur3d pointdecollision) {

		double dScalaire = (2 - mapRestitution[objet.obtMateriaux()]) * objet.obtVitesse().produitScalaire(vecteurNormal);
		objet.obtVitesse() -= vecteurNormal * dScalaire;
	}

	//void rebondObjetCarte(Objet& objet, Vecteur3d vecteurNormal, Vecteur3d pointdecollision) {

	//	Vecteur3d* BoiteDeCollisionModifiee = objet.obtModele3D()->obtBoiteDeCollisionModifiee();

	//	Vecteur3d positionCM = { 0, 0, 0 };

	//	for (unsigned int i = 0; i < 8; i++) {
	//		positionCM.x += BoiteDeCollisionModifiee[i].x;
	//	}
	//	for (unsigned int i = 0; i < 8; i++) {
	//		positionCM.y += BoiteDeCollisionModifiee[i].y;
	//	}
	//	for (unsigned int i = 0; i < 8; i++) {
	//		positionCM.z += BoiteDeCollisionModifiee[i].z;
	//	}
	//	positionCM /= 8;

	//	Vecteur3d rayon = { positionCM.x - pointdecollision.x, positionCM.y - pointdecollision.y, positionCM.z - pointdecollision.z };

	//	double cr = 1 - mapRestitution[objet.obtMateriaux()];
	//	double r = rayon.norme();
	//	double theta = sin(vecteurNormal.angleEntreVecteurs(rayon));
	//	double masse = objet.obtMasse();
	//	double vi = objet.obtVitesse().norme();
	//	double wi = objet.obtVitesseAngulaire().norme();

	//	// Pour le calcul du moment d'inertie...
	//	Vecteur3d  coteX = { BoiteDeCollisionModifiee[7].x - BoiteDeCollisionModifiee[4].x,
	//		BoiteDeCollisionModifiee[7].y - BoiteDeCollisionModifiee[4].y,
	//		BoiteDeCollisionModifiee[7].z - BoiteDeCollisionModifiee[4].z };
	//	double longueurcoteX = coteX.norme();
	//	coteX.normaliser();

	//	Vecteur3d coteY = { BoiteDeCollisionModifiee[5].x - BoiteDeCollisionModifiee[4].x,
	//		BoiteDeCollisionModifiee[5].y - BoiteDeCollisionModifiee[4].y,
	//		BoiteDeCollisionModifiee[5].z - BoiteDeCollisionModifiee[4].z };
	//	double longueurcoteY = coteY.norme();
	//	coteY.normaliser();

	//	Vecteur3d coteZ = { BoiteDeCollisionModifiee[0].x - BoiteDeCollisionModifiee[4].x,
	//		BoiteDeCollisionModifiee[0].y - BoiteDeCollisionModifiee[4].y,
	//		BoiteDeCollisionModifiee[0].z - BoiteDeCollisionModifiee[4].z };
	//	double longueurcoteZ = coteZ.norme();
	//	coteZ.normaliser();

	//	rayon.normaliser();
	//	vecteurNormal.normaliser();
	//	Vecteur3d axederotation = rayon.produitVectoriel(vecteurNormal);
	//	axederotation.normaliser();

	//	double I = calculerMomentInertie(axederotation, coteX, coteY, coteZ, longueurcoteX, longueurcoteY, longueurcoteZ, masse);

	//	double a = (masse / 2)*(1 + (masse*pow(r, 2)*pow(theta, 2)) / (I));
	//	double b = (-pow(masse, 2)*pow(r, 2)*pow(theta, 2)*vi) / I;
	//	double c = (masse*pow(vi, 2) / 2) * (((masse*pow(r, 2)*pow(theta, 2)) / (I)) - (pow(cr, 2)));

	//	double vitesseFinale = (-b - sqrt(pow(b, 2) - 4 * a*c)) / (2 * a);

	//	double wf = (r * masse * (vitesseFinale - vi) * theta) / I * 20;

	//	Vecteur3d vvitesseAngulaire = axederotation * wf;
	//	objet.defVitesseAngulaire(vvitesseAngulaire);
	//	objet.obtVitesse().normaliser();

	//	double dScalaire = (2 - mapRestitution[objet.obtMateriaux()]) * objet.obtVitesse().produitScalaire(vecteurNormal);
	//	objet.obtVitesse() -= vecteurNormal * dScalaire;
	//	objet.obtVitesse() *= vitesseFinale;
	//}

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

	void appliquerVent(Vecteur3d vecteurVitesseVent, Vecteur3d& vitesseObjet, gfx::Modele3D* modele, double masse, double frametime) {

		double* tableaunormale = modele->obtNormalesModifies(); //À MODIFIER LORSQUE LES MODIF DE normale FONCTIONNENT!
		double* tableauVertices = modele->obtSommetsModifies();

		double accelerationSelonForceVent = 0.5 * 1.204 * pow(vecteurVitesseVent.norme(), 2);

		double coefficientTrainer = 0;
		double surface = 0;

		double nombreVertice = modele->obtModele()->obtNbrVertices();

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
		accelerationSelonForceVent *= (coefficientTrainer * surface / masse);

		// Mise en proportion pour l'addition...
		vecteurVitesseVent.normaliser();

		// Nécéssite l'ajout d'un division par le temps...
		Vecteur3d vecteurVitesseAppliquer = { accelerationSelonForceVent * vecteurVitesseVent.x, accelerationSelonForceVent * vecteurVitesseVent.y, accelerationSelonForceVent * vecteurVitesseVent.z };

		vitesseObjet += vecteurVitesseAppliquer * frametime;
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

			if (collisionDroiteModele(modeleSalle, rayonCollision, pointCollision, normale, nullptr, true)) {

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
						joueur->defPosition(Vecteur3d(joueur->obtPosition().x + pointDifference.x, joueur->obtPosition().y, joueur->obtPosition().z + pointDifference.z));
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

		for (auto it : listeObjet) {

			if (!it->obtCollisionInterne()) {
				if (it->obtModele3D()->obtBoiteCollision().collisionDeuxBoite(joueur->obtModele3D()->obtBoiteCollision())) {
					joueur->defEtat(STABLE);
					joueur->obtVitesse().y = 0.f;
					joueur->obtVitesse().x = 0.f;
					joueur->obtVitesse().z = 0.f;
					return true;
				}
			}
			if (it->obtCollisionInterne()) {
				if (collisionDroiteModele(it->obtModele3D(), rayonCollision, pointCollision, normale, nullptr, true)) {
					joueur->defNormale(normale);
					joueur->defPointCollision(pointCollision);
					Vecteur3d pointDiference = pointCollision - point;
					joueur->defPosition(joueur->obtPosition() + pointDiference);
					joueur->defEtat(STABLE);
					joueur->obtVitesse().y = 0.f;
					joueur->obtVitesse().x = 0.f;
					joueur->obtVitesse().z = 0.f;
					return true;
				}
			}
		}
		return false;
	}

};