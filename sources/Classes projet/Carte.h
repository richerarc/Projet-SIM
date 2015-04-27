#pragma once
#include <map>
#include <tuple>
#include <list>
#include <vector>
#include <fstream>
#include <cmath>
#include "Modele3D.h"
#include "Porte.h"
#include "Salle.h"
#include "Info.h"
#include "Graphe.h"
#include "GestionnaireChemin.h"
#include "Gestionnaire3D.h"
#include "LecteurFichier.h"
#include "Joueur.h"
#include "Physique.h"

typedef std::tuple<unsigned int, unsigned int, bool> Entree;
typedef std::tuple<unsigned int, unsigned int> Sortie;
typedef std::tuple<char*, char*, char*> Modele_Text;

class Carte : public Singleton < Carte > {
private:
	graphe::Graphe carte;
	std::map<Entree, Sortie> liens;
	std::list<InfoSalle> infosSalles;
	gfx::Modele3D *modeleMur;
	gfx::Modele3D *modelePorte;

	std::vector<Modele_Text> cheminsModeleText;

	void ajouterLien(Entree entree, Sortie sortie){
		liens[entree] = sortie;
	}

	void creerSalle(InfoSalle& infoSalleActive, bool enPositionnement) {

		salleActive = new Salle(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(infoSalleActive.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(infoSalleActive.cheminTexture)), infoSalleActive.nbrPorte, infoSalleActive.ID);
		salleActive->defEchelle(infoSalleActive.echelle);

		double orientation;
		for (auto& it : infoSalleActive.Objet) {
			if (!enPositionnement) {
				gfx::Modele3D* modeleporte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(it.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(it.cheminTexture));
				modeleporte->defPosition(it.position);
				modeleporte->defOrientation(0, it.rotation, 0);
				salleActive->ajoutObjet(new Porte(modeleporte, it.ID, "metal", it.position, { 0, 0, 0 }, false, true, false, false));
			}
			else {
				// Tests de positionnement de la porte avec collision
				gfx::Modele3D* modeleporte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(it.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(it.cheminTexture));
				modeleporte->defPosition(it.position);
				modeleporte->defOrientation(0, it.rotation, 0);

				Objet* porte = new Porte(modeleporte, it.ID, "metal", it.position, { 0, 0, 0 }, false, true, false, false);
				porte->defVitesse(it.direction);
				porte->defPosition(Vecteur3d(porte->obtPosition().x, porte->obtPosition().y + 1.74, porte->obtPosition().z));
				while (!Physique::obtInstance().collisionPorte(salleActive->obtModele(), *porte, orientation)) {
					porte->defPosition(porte->obtPosition() + (it.direction / 10));
				}
				porte->defPosition(Vecteur3d(porte->obtPosition().x, porte->obtPosition().y - 1.74, porte->obtPosition().z));
				porte->obtModele3D()->defOrientation(porte->obtModele3D()->obtOrientation() + Vecteur3d(0, orientation, 0));

				it.position = porte->obtPosition();
				it.rotation = porte->obtModele3D()->obtOrientation().y;
				delete porte;
				int iii = 0;
			}
		}
		if (enPositionnement) {
			delete salleActive;
		}
	}

public:

	Salle *salleActive;

	void destination(std::tuple<unsigned int, unsigned int, bool> sortie, Joueur& joueur) {

		delete salleActive;

		Sortie pieceSuivante = liens[sortie];

		auto debut = infosSalles.begin();
		std::advance(debut, std::get<0>(pieceSuivante));

		creerSalle(*debut, false);

		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modeleMur);
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modelePorte);

		// Positionnement du joueur...
		auto it = (*debut).Objet.begin();
		std::advance(it, std::get<1>(pieceSuivante));
		Vecteur3d vecteur;
		Vecteur3d vecteurMur;
		//switch ((int)(*it).rotation) { // Enlever les switch et calculer en fonction des angles et it = porte.
		//case 0:
		//	vecteur = { (*it).position.x + 1.2, (*it).position.y, (*it).position.z - 0.5 };
		//	joueur.defPosition((*it).position);
		//	vecteurMur = { (*it).position.x + 2.5, (*it).position.y, (*it).position.z };
		//	modeleMur->defOrientation(0, 0, 0);
		//	modelePorte->defOrientation(0, 0, 0);
		//	modeleMur->defOrientation(0, (*it).rotation, 0);
		//	modelePorte->defOrientation(0, (*it).rotation + 180, 0);
		//	modeleMur->defPosition(vecteurMur);
		//	modelePorte->defPosition(vecteurMur.x, vecteurMur.y, vecteurMur.z - 1.0);
		//	break;
		//case 90:
		//	vecteur = { (*it).position.x - 0.5, (*it).position.y, (*it).position.z - 1.2 };
		//	joueur.defPosition((*it).position);
		//	vecteurMur = { (*it).position.x, (*it).position.y, (*it).position.z - 2.5 };
		//	modeleMur->defOrientation(0, 0, 0);
		//	modelePorte->defOrientation(0, 0, 0);
		//	modeleMur->defOrientation(0, (*it).rotation, 0);
		//	modelePorte->defOrientation(0, -(*it).rotation, 0);
		//	modeleMur->defPosition(vecteurMur);
		//	modelePorte->defPosition(vecteurMur.x - 1.0, vecteurMur.y, vecteurMur.z);
		//	break;
		//case -90:
		//	vecteur = { (*it).position.x + 0.5, (*it).position.y, (*it).position.z + 1.2 };
		//	joueur.defPosition((*it).position);
		//	vecteurMur = { (*it).position.x, (*it).position.y, (*it).position.z + 2.5 };
		//	modeleMur->defOrientation(0, 0, 0);
		//	modelePorte->defOrientation(0, 0, 0);
		//	modeleMur->defOrientation(0, (*it).rotation, 0);
		//	modelePorte->defOrientation(0, -(*it).rotation, 0);
		//	modeleMur->defPosition(vecteurMur);
		//	modelePorte->defPosition(vecteurMur.x + 1.0, vecteurMur.y, vecteurMur.z);
		//	break;
		//case 180:
		//	vecteur = { (*it).position.x - 1.2, (*it).position.y, (*it).position.z + 0.5 };
		//	joueur.defPosition((*it).position);
		//	vecteurMur = { (*it).position.x - 2.5, (*it).position.y, (*it).position.z };
		//	modeleMur->defOrientation(0, 0, 0);
		//	modelePorte->defOrientation(0, 0, 0);
		//	modeleMur->defOrientation(0, (*it).rotation, 0);
		//	modelePorte->defOrientation(0, (*it).rotation - 180, 0);
		//	modeleMur->defPosition(vecteurMur);
		//	modelePorte->defPosition(vecteurMur.x, vecteurMur.y, vecteurMur.z + 1.0);
		//	break;
		//}


		//joueur.defAngleHorizontal(-joueur.obtHAngle());
		vecteur = { (*it).position.x + (-1.2 * (*it).direction.x) + (-0.5 * (*it).direction.z), (*it).position.y, (*it).position.z + (-1.2 * (*it).direction.z) + (-0.5 * (*it).direction.x) };
		vecteurMur = { (*it).position.x + (-2.5 * (*it).direction.x), (*it).position.y, (*it).position.z + (-2.5 * (*it).direction.z) };
		modeleMur->defPosition(vecteurMur);
		modelePorte->defPosition(vecteurMur.x + (-1 * (*it).direction.z), vecteurMur.y, vecteurMur.z + (1 * (*it).direction.x)); // Probs ici
		modeleMur->defOrientation(0, (*it).rotation, 0);
		modelePorte->defOrientation(0, (*it).rotation + 180, 0); // Angles pas legit gotta fix it.
		//joueur.defAngleHorizontal();
		joueur.defPosition(vecteur);
	}

	// Procédure qui permet de créer le graphe et la première salle dans laquelle le joueur commence...
	// En entrée:
	// Param1: Le nombre de salle easy = 12, normal = 20, difficile = 32.
	void creer(const unsigned int nombreDeSalle) {

		// Création du graphe
		carte.creer(nombreDeSalle);
		int itterateurPorte(0);

		int* porte = new int[nombreDeSalle];
		Entree entree;
		Sortie sortie;
		for (unsigned int i = 0; i < nombreDeSalle; ++i)
			porte[i] = 0;

		for (unsigned int i = 0; i < nombreDeSalle; ++i){
			itterateurPorte = 0;
			for (unsigned int j = 0; j < nombreDeSalle; ++j){
				if (carte.matrice[i * nombreDeSalle + j]){
					entree = std::make_tuple(i, itterateurPorte++, false);
					sortie = std::make_tuple(j, porte[j]);
					++porte[j];
					ajouterLien(entree, sortie);

				}
			}
		}

		// Load des salles possibles
		std::ifstream fichierSalle("salle_text.txt");
		std::ifstream fichierObjet("objet_text.txt");

		int itterateur(0);
		while (!fichierSalle.eof()) {
			char* curseur1 = new char[20];
			char* curseur2 = new char[20];
			char* curseur3 = new char[20];
			fichierSalle >> curseur1; fichierSalle >> curseur2; fichierSalle >> curseur3;
			cheminsModeleText.push_back(Modele_Text(curseur1, curseur2, curseur3));
			++itterateur;
		}

		unsigned int aleatoire;
		unsigned int pos;
		double randomRatio;
		bool directionPossible;
		bool boPorte;
		double x(0), y(0), z(0), xMin, xMax, yMin, yMax, zMin, zMax;
		Vecteur3d pos3D(0, 0, 0);
		InfoObjet objet;
		InfoSalle salle;

		// Boucle sur toutes les salles...
		for (unsigned int i = 0; i < nombreDeSalle; ++i){

			salle.ID = i;
			salle.nbrPorte = carte.degreSortant(i);
			salle.echelle = { rand() % 3 + 2.0, 2.0, rand() % 3 + 2.0 };
			//aleatoire = rand() % itterateur;
			aleatoire = rand() % 3; // en attendant que toutes elles salles sont conformes
			salle.cheminModele = (char*)(std::get<0>(cheminsModeleText[aleatoire]));
			salle.cheminTexture = (char*)(std::get<1>(cheminsModeleText[aleatoire]));
			LecteurFichier::lireBoite((char*)(std::get<2>(cheminsModeleText[aleatoire])), salle);

			// Boucle sur toutes les portes d'un salle pour les positionner...
			for (unsigned short IDPorte = 0; IDPorte < salle.nbrPorte; ++IDPorte) {
				objet.ID = IDPorte;
				objet.cheminModele = "portePlate.obj";// "HARDCODÉ"
				objet.cheminTexture = "portePlate.png";// "HARDCODÉ"
				boPorte = false;
				while (!boPorte) {

					// Obtenir des coordonnés de la d'une boîte de collision de la salle.
					boPorte = true;
					auto it = salle.boitesCollision.begin();
					pos = rand() % salle.boitesCollision.size();
					std::advance(it, pos);
					do{
						xMin = (*it).obtBoite()[rand() % 8].x;
						xMax = (*it).obtBoite()[rand() % 8].x;
					} while (xMin == xMax);
					if (xMax < xMin){
						x = xMin;
						xMin = xMax;
						xMax = x;
					}
					x = xMax - xMin;
					do{
						yMin = (*it).obtBoite()[rand() % 8].y;
						yMax = (*it).obtBoite()[rand() % 8].y;
					} while (yMin == yMax);
					if (yMax < yMin){
						y = yMin;
						yMin = yMax;
						yMax = y;
					}
					y = yMax - yMin;
					do{
						zMin = (*it).obtBoite()[rand() % 8].z;
						zMax = (*it).obtBoite()[rand() % 8].z;
					} while (zMin == zMax);
					if (zMax < zMin){
						z = zMin;
						zMin = zMax;
						zMax = z;
					}
					z = zMax - zMin;

					// Positionnement de la porte...
					pos3D.y = yMin;
					directionPossible = false;
					while (!directionPossible)
					{
						switch (rand() % 4) {
						case 0:

							if (z >= 1) {

								randomRatio = (double)rand() / RAND_MAX;
								pos3D.x = xMin + randomRatio * (x);

								do {
									randomRatio = (double)rand() / RAND_MAX;
									pos3D.z = zMin + randomRatio * (z);
								} while ((pos3D.z < zMin) || (pos3D.z > zMax - 1));

								directionPossible = true;
								objet.direction = { 1, 0, 0 };
								objet.rotation = 180;
							}

							break;
						case 1:

							if (z >= 1) {

								randomRatio = (double)rand() / RAND_MAX;
								pos3D.x = xMin + randomRatio * (x);

								do {
									randomRatio = (double)rand() / RAND_MAX;
									pos3D.z = zMin + randomRatio * (z);
								} while ((pos3D.z < zMin + 1) || (pos3D.z > zMax));

								directionPossible = true;
								objet.direction = { -1, 0, 0 };
								objet.rotation = 0;
							}

							break;
						case 2:

							if (x >= 1) {

								do {
									randomRatio = (double)rand() / RAND_MAX;
									pos3D.x = xMin + randomRatio * (x);
								} while ((pos3D.x < xMin + 1) || (pos3D.x > xMax));

								randomRatio = (double)rand() / RAND_MAX;
								pos3D.z = zMin + randomRatio * (z);

								directionPossible = true;
								objet.direction = { 0, 0, 1 };
								objet.rotation = 90;
							}

							break;
						case 3:

							if (x >= 1) {

								do {
									randomRatio = (double)rand() / RAND_MAX;
									pos3D.x = xMin + randomRatio * (x);
								} while ((pos3D.x < xMin) || (pos3D.x > xMax - 1));

								randomRatio = (double)rand() / RAND_MAX;
								pos3D.z = zMin + randomRatio * (z);

								directionPossible = true;
								objet.direction = { 0, 0, -1 };
								objet.rotation = -90;
							}

							break;
						}
					}

					// Boucle qui vérifie si une porte sera en collision avec une autre...
					for (auto it : salle.Objet) {

						// Si les portes ont la même direction...
						if (objet.direction == it.direction) {

							// Axe x
							switch ((int)objet.direction.x) {
							case 1:
								if ((pos3D.z >= it.position.z && pos3D.z <= it.position.z + 1) || (pos3D.z + 1 >= it.position.z && pos3D.z + 1 <= it.position.z + 1)) {
									boPorte = false;
								}
								break;
							case -1:
								if ((pos3D.z <= it.position.z && pos3D.z >= it.position.z - 1) || (pos3D.z - 1 <= it.position.z && pos3D.z - 1 >= it.position.z - 1)) {
									boPorte = false;
								}
								break;
							}

							// Axe z
							switch ((int)objet.direction.z) {
							case 1:
								if ((pos3D.x <= it.position.x && pos3D.x >= it.position.x - 1) || (pos3D.x - 1 <= it.position.x && pos3D.x - 1 >= it.position.x - 1)) {
									boPorte = false;
								}
								break;
							case -1:
								if ((pos3D.x >= it.position.x && pos3D.x <= it.position.x + 1) || (pos3D.x + 1 >= it.position.x && pos3D.x + 1 <= it.position.x + 1)) {
									boPorte = false;
								}
								break;
							}
						}
					}

				}

				// Ajout de l'objet.
				objet.position = pos3D;
				salle.Objet.push_back(objet);
			}

			// Ajout et réinitialisation de la salle.
			infosSalles.push_back(salle);
			salle.boitesCollision.clear();
			salle.Objet.clear();
		}


		for (auto& it : infosSalles) {
			creerSalle(it, true);
		}

		auto debut = infosSalles.begin();
		pos = rand() % infosSalles.size();
		std::advance(debut, pos);

		creerSalle(*debut, false);

		modeleMur = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("murSalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("murSalle.png"));
		modelePorte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("portePlate.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("portePlate.png"));
		modeleMur->defOrientation(0, 0, 0);
		modelePorte->defOrientation(0, 0, 0);
	}
};
