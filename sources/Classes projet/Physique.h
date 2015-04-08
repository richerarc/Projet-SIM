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
	double sensibiliteMagnetique;
	std::map<char*, double> mapRestitution;
	bool collision;

	bool collisionDroiteModele(gfx::Modele3D* modele3D, Droite& rayonCollision, Vecteur3d& pointCollision, Vecteur3d& normale) {

		Vecteur3d point1;
		Vecteur3d point2;
		Vecteur3d point3;
		Vecteur3d point;
		double* tabVertices;
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
			normale = { modele->obtNormales()[Nbrface * 3], modele->obtNormales()[Nbrface * 3 + 1], modele->obtNormales()[Nbrface * 3 + 2]};

			if (plan.insertionDroitePlan(rayonCollision, pointCollision)) {

				point = pointCollision + rayonCollision.obtenirVecteurDirecteur();

				if (pointDansFace(point1, point2, point3, pointCollision, normale)) {
					if (memeCote(point, rayonCollision.obtenirPoint(), pointCollision, point1)) {

						double angle = normale.angleEntreVecteurs(rayonCollision.obtenirVecteurDirecteur()) * (180 / M_PI);
						if (angle > 120 && angle < 260)
							return true;
					}
				}
			}
		}
		return false;
	}

	bool collisionDroiteObjet(Objet& objet, Droite& rayonCollision, Vecteur3d& pointCollision, Vecteur3d& normale) {

		Vecteur3d point1;
		Vecteur3d point2;
		Vecteur3d point3;
		Vecteur3d point;
		Vecteur3d* boiteCollision = objet.obtModele3D()->obtBoiteDeCollisionModifiee();
		Plan plan;
		gfx::Modele* modele = objet.obtModele3D()->obtModele();

		for (unsigned int Nbrface = 0; Nbrface < 8; Nbrface ++) {

			for (int j = 0; j < 3; j++) {
				switch (j) {

					case 0:
						point1 = boiteCollision[Nbrface * 3 + j];
						break;

					case 1:
						point2 = boiteCollision[Nbrface * 3 + j];
						break;

					case 2:
						point3 = boiteCollision[Nbrface * 3 + j];
						break;
				}
			}

			plan.calculerPlan(point1, point2, point3);
			if (plan.insertionDroitePlan(rayonCollision, pointCollision)) {

				point = pointCollision + rayonCollision.obtenirVecteurDirecteur();

				if (pointDansFace(point1, point2, point3, pointCollision, normale)) {

					if (memeCote(point, rayonCollision.obtenirPoint(), pointCollision, point1)) {

						normale = plan.obtenirNormale();
						double angle = normale.angleEntreVecteurs(rayonCollision.obtenirVecteurDirecteur()) * (180 / M_PI);

						if (angle > 120 && angle < 240)
							return true;
					}
				}
			}
		}
		return false;
	}	

	bool memeCote(Vecteur3d point1, Vecteur3d point2, Vecteur3d droite1, Vecteur3d droite2) {

		Vecteur3d produit1 = (droite2 - droite1).produitVectoriel(point1 - droite1);
		Vecteur3d produit2 = (droite2 - droite1).produitVectoriel(point2 - droite1);
		if (produit1.produitScalaire(produit2) >= 0)
			return true;
		return false;
	}

public:

	Physique() {
		constanteDeFriction = 0.5;
		gravite = -9.8;
		sensibiliteMagnetique = 0.0072;
		collision = false;

		// Ajout des coefficients de restitution des diff�rents mat�riaux
		mapRestitution["metal"] = 0.9;
		mapRestitution["bois"] = 0.5;
		mapRestitution["plastic"] = 0.68;
		mapRestitution["ballerebondissante"] = 0.1;
	}

	void appliquerPhysiqueSurListeObjet(float frameTime) {
		
		std::list<Objet*> objets = Carte::obtInstance().salleActive->obtListeObjet();

		for (auto it : objets) {
			if (it->obtMasse() != 0) {
				appliquerGravite(it->obtVitesse(), frameTime);
			}
			Vent* it_Vent = dynamic_cast<Vent*>(it);
			if (it_Vent != nullptr) {
				for (auto it_Objet : objets) {
					if (it_Objet->obtMasse() != 0) {
						/*
						if (it_Objet->obtModele3D().obtPosition().x >= it->obtPosition().x && it_Objet->obtModele3D().obtPosition().x <= it->obtPosition().x + it->obtDimensions().x) {
						if (it_Objet->obtModele3D().obtPosition().y >= it->obtPosition().y && it_Objet->obtModele3D().obtPosition().y <= it->obtPosition().y + it->obtDimensions().y) {
						if (it_Objet->obtModele3D().obtPosition().z >= it->obtPosition().z && it_Objet->obtModele3D().obtPosition().z <= it->obtPosition().z + it->obtDimensions().z) {
						Physique::obtInstance().appliquerVent(it->obtVitesse(), *it_Objet, frameTime);
						}
						}
						}
						*/
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
			ObjetFixe* it_ObjetFixe = dynamic_cast<ObjetFixe*>(it);
			if (it_ObjetFixe != nullptr) {
				for (auto it_Objet : objets) {
					if (it_Objet->obtMasse() != 0) {
						// collisions

					}
				}
			}
		}
	}


	void RebondObjetCarte(Objet& objet, Vecteur3d vecteurNormal, Vecteur3d pointdecollision) {

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

		double cr = 1 - mapRestitution[objet.obtMateriaux()];
		double r = rayon.norme();
		double theta = sin(vecteurNormal.angleEntreVecteurs(rayon));
		double masse = objet.obtMasse();
		double vi = objet.obtVitesse().norme();
		double wi = objet.obtVitesseAngulaire().norme();

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

		rayon.normaliser();
		vecteurNormal.normaliser();
		Vecteur3d axederotation = rayon.produitVectoriel(vecteurNormal);
		axederotation.normaliser();

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

	// Proc�dure qui donne le moment d'inertie d'un rectangle, tous les vecteurs doivent �tre normalis�s(unitaires).
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

	void RebondObjetObjet(Objet& objet1, Objet& objet2, Vecteur3d vecteurNormal) {

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

		double* tableaunormale = objet.obtModele3D()->obtNormalesModifies(); //� MODIFIER LORSQUE LES MODIF DE normale FONCTIONNENT!
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

			// Si l'angle entre le vecteur normal et le vecteur du vent est n�gatif
			if (angleEntreVecteursVentNormale < 0) {

				coefficientTrainer += abs(angleEntreVecteursVentNormale);
				// Calcul de la surface selon la formule d'h�ron: sqrt(s(s-a)(s-b)(s-c))

				// a : Point 1 � point 2;
				double a = sqrt(pow(tableauVertices[parcoursFace] - tableauVertices[parcoursFace + 3], 2) +
					pow(tableauVertices[parcoursFace + 1] - tableauVertices[parcoursFace + 4], 2) +
					pow(tableauVertices[parcoursFace + 2] - tableauVertices[parcoursFace + 5], 2));

				// a : Point 1 � point 3;
				double b = sqrt(pow(tableauVertices[parcoursFace] - tableauVertices[parcoursFace + 6], 2) +
					pow(tableauVertices[parcoursFace + 1] - tableauVertices[parcoursFace + 7], 2) +
					pow(tableauVertices[parcoursFace + 2] - tableauVertices[parcoursFace + 8], 2));

				// a : Point 2 � point 3;
				double c = sqrt(pow(tableauVertices[parcoursFace + 3] - tableauVertices[parcoursFace + 6], 2) +
					pow(tableauVertices[parcoursFace + 4] - tableauVertices[parcoursFace + 7], 2) +
					pow(tableauVertices[parcoursFace + 5] - tableauVertices[parcoursFace + 8], 2));

				// Demi-p�rim�tre;
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

		// N�c�ssite l'ajout d'un division par le temps...
		Vecteur3d vecteurVitesseAppliquer = { accelerationSelonForceVent * vecteurVitesseVent.x, accelerationSelonForceVent * vecteurVitesseVent.y, accelerationSelonForceVent * vecteurVitesseVent.z };

		objet.obtVitesse() += vecteurVitesseAppliquer * frametime;
	}
	
	// MANQUE LA NORMALE
	void appliquerFrottement(Objet& objet) {
		//objet.obtVitesse().soustraire(constanteDeFriction * obtenirForceNormale(objet.obtMasse(), objet.obtPosition()));
	}
	
	// Proc�dure qui applique la force d'attraction magn�tique sur un objet
	// (La force du champs et la sensibilit� magn�tique de l'objet sont constant).
	void appliquerMagnetisme(Objet& objet, Vecteur3d positionAimant, double force, double frametime) {

		double distanceObjetAimant = distanceEntreDeuxPoints(positionAimant, objet.obtPosition());
		double accelerationMagnetique = (6 * sensibiliteMagnetique * force) / (objet.obtMasse() * distanceObjetAimant);

		Vecteur3d vecteurProportionnel = { positionAimant.x - objet.obtPosition().x, positionAimant.y - objet.obtPosition().y, positionAimant.z - objet.obtPosition().z };
		vecteurProportionnel.normaliser();

		Vecteur3d vecteurAcceleration = { accelerationMagnetique, accelerationMagnetique, accelerationMagnetique };

		vecteurAcceleration.produitParUnVecteur(vecteurProportionnel);

		objet.obtVitesse() += vecteurAcceleration * frametime;

	}

	double obtenirAnglePenduleSimple(double angleMaximal, double omega, double frametime) {
		return angleMaximal * SDL_cos(omega * frametime);
	}

	double distanceEntreDeuxPoints(Vecteur3d point1, Vecteur3d point2) {
		return SDL_sqrt(SDL_pow((point2.x - point1.x), 2) + SDL_pow((point2.y - point1.y), 2) + SDL_pow((point2.z - point1.z), 2));
	}

	bool pointDansFace(Vecteur3d& point1, Vecteur3d& point2, Vecteur3d& point3, Vecteur3d& point, Vecteur3d normale) {

		Vecteur3d v0 = point3 - point1;
		Vecteur3d v1 = point2 - point1;
		Vecteur3d v2 = point - point1;

		Vecteur2d vect0;
		Vecteur2d vect1;
		Vecteur2d vect2;

		normale.normaliser();

		double x = fabs(normale.x);
		double y = fabs(normale.y);
		double z = fabs(normale.z);

		if (x > y && x > z) {

			vect0 = Vecteur2d(v0.y, v0.z);
			vect1 = Vecteur2d(v1.y, v1.z);
			vect2 = Vecteur2d(v2.y, v2.z);
		}

		if (y > x && y > z) {

			vect0 = Vecteur2d(v0.x, v0.z);
			vect1 = Vecteur2d(v1.x, v1.z);
			vect2 = Vecteur2d(v2.x, v2.z);
		}
		if (z > x && z > y) {

			vect0 = Vecteur2d(v0.x, v0.y);
			vect1 = Vecteur2d(v1.x, v1.y);
			vect2 = Vecteur2d(v2.x, v2.y);
		}

		double produit00 = vect0.produitScalaire(vect0);
		double produit01 = vect0.produitScalaire(vect1);
		double produit02 = vect0.produitScalaire(vect2);
		double produit11 = vect1.produitScalaire(vect1);
		double produit12 = vect1.produitScalaire(vect2);

		double invDenom = 1 / (produit00 * produit11 - produit01 * produit01);
		double u = (produit11 * produit02 - produit01 * produit12) * invDenom;
		double v = (produit00 * produit12 - produit12 * produit02) * invDenom;

		return (u >= 0) && (v >= 0) && (u + v < 1);

	}

	double obtenirEnergieCinetique(double masse, Vecteur3d& vecteurVitesseObjet) {
		return 0.5 * masse * SDL_pow(vecteurVitesseObjet.norme(), 2);
	}

	bool collisionObjetSalle(Objet& objet) {
		Droite rayonCollision;
		Vecteur3d pointCollision;
		Vecteur3d point;
		Vecteur3d normale;
		Vecteur3d difference;
		Vecteur3d* tabObjet = objet.obtModele3D()->obtBoiteDeCollisionModifiee();
		Salle* salle = Carte::obtInstance().salleActive;

		for (int i = 0; i < 8; i++) {

			point = tabObjet[i];

			rayonCollision = Droite(point, objet.obtVitesse());

			if (collisionDroiteModele(salle->obtModele(), rayonCollision, pointCollision, normale)) {
				
				difference = pointCollision - point;
				objet.defPosition(objet.obtPosition() + difference);

				normale.normaliser();
				RebondObjetCarte(objet, normale, pointCollision);
				return true;
			}
		}

		
		std::list<Objet*> list = salle->obtListeObjet();

		if (!collision) {

			for (int i = 0; i < 8; i++) {

				point = tabObjet[i];
				rayonCollision = Droite(point, objet.obtVitesse());

				for (auto it : list) {

					if (collisionDroiteObjet(*it, rayonCollision, pointCollision, normale)) {

						RebondObjetObjet(objet, *it, normale);
						collision = true;
						return true;
					}
				}
			}
		}
		else
			collision = false;


		return false;
	}

	bool collisionJoueurSalle(Joueur &joueur) {
		Droite rayonCollision;
		Vecteur3d pointCollision;
		Vecteur3d point;
		Vecteur3d normale;
		Vecteur3d* tabJoueur = joueur.obtModele3D()->obtBoiteDeCollisionModifiee();
		Salle* salle = Carte::obtInstance().salleActive;

		for (int i = 0; i < 8; i++) {

			point = tabJoueur[i];

			rayonCollision = Droite(point, joueur.obtVitesse());

			if (collisionDroiteModele(salle->obtModele(), rayonCollision, pointCollision, normale)) {
				Vecteur3d pointDiference = pointCollision - point;
				joueur.defPosition(joueur.obtPosition() + pointDiference);

				return true;
			}
		}

		return false;
	}

	bool collisionJoueurObjet(Joueur &joueur, Objet &objet) {
		Droite rayonCollision;
		Vecteur3d pointCollision;
		Vecteur3d point;
		Vecteur3d normale;
		Vecteur3d* tabJoueur = joueur.obtModele3D()->obtBoiteDeCollisionModifiee();

		for (int i = 0; i < 8; i++) {
			point = tabJoueur[i];

			rayonCollision = Droite(point, joueur.obtVitesse());

			if (collisionDroiteObjet(objet, rayonCollision, pointCollision, normale)) {
				Vecteur3d pointDiference = pointCollision - point;
				joueur.defPosition(joueur.obtPosition() + pointDiference);

				return true;
			}
		}
		return false;
	}

};