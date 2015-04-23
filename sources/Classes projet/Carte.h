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
typedef std::tuple<std::string, std::string, std::string> Modele_Text;

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

public:

	Salle *salleActive;

	void destination(std::tuple<unsigned int, unsigned int, bool> sortie, Joueur& joueur){

		for (auto it : salleActive->obtListeObjet()) {
			gfx::Gestionnaire3D::obtInstance().retObjet(it->obtModele3D());
		}

		gfx::Gestionnaire3D::obtInstance().retObjet(salleActive->obtModele());

		Sortie pieceSuivante = liens[sortie];

		auto debut = infosSalles.begin();
		std::advance(debut, std::get<0>(pieceSuivante));

		salleActive = new Salle(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele((*debut).cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture((*debut).cheminTexture)), (*debut).nbrPorte, (*debut).ID);
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modeleMur);
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modelePorte);
		salleActive->defEchelle((*debut).echelle);
		auto it = (*debut).Objet.begin();
		for (unsigned int i = 0; i < (*debut).Objet.size(); ++i) {
			gfx::Modele3D* modeleporte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele((*it).cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture((*it).cheminTexture));
			modeleporte->defPosition((*it).position);
			modeleporte->defOrientation(0, (*it).rotation, 0);
			Objet* porte = new Porte(modeleporte, (*it).ID, "Metal", (*it).position, { 0, 0, 0 }, false, true, false, false);
			porte->defVitesse((*it).direction);
			porte->defPosition(Vecteur3d(porte->obtPosition().x, porte->obtPosition().y + 0.2, porte->obtPosition().z));
			while (!Physique::obtInstance().collisionObjetSalle(salleActive, *porte, false)) {
				porte->defPosition(porte->obtPosition() + ((*it).direction / 10));
			}
			porte->defPosition(Vecteur3d(porte->obtPosition().x, porte->obtPosition().y - 0.2, porte->obtPosition().z));

			salleActive->ajoutObjet(porte);
			if (std::get<1>(sortie) == i) {
				Vecteur3d vecteur;
				Vecteur3d vecteurMur;
				switch ((*it).rotation) {
				case 0:
					vecteur = { modeleporte->obtPosition().x + 1.2, modeleporte->obtPosition().y, modeleporte->obtPosition().z - 0.5 };
					joueur.defPosition(modeleporte->obtPosition());
					vecteurMur = { modeleporte->obtPosition().x + 2.5, modeleporte->obtPosition().y, modeleporte->obtPosition().z };
					modeleMur->defOrientation(0, 0, 0);
					modelePorte->defOrientation(0, 0, 0);
					modeleMur->defOrientation(0, (*it).rotation, 0);
					modelePorte->defOrientation(0, (*it).rotation + 180, 0);
					modeleMur->defPosition(vecteurMur);
					modelePorte->defPosition(vecteurMur.x, vecteurMur.y, vecteurMur.z - 1.0);
					break;
				case 90:
					vecteur = { modeleporte->obtPosition().x - 0.5, modeleporte->obtPosition().y, modeleporte->obtPosition().z - 1.2 };
					joueur.defPosition(modeleporte->obtPosition());
					vecteurMur = { modeleporte->obtPosition().x, modeleporte->obtPosition().y, modeleporte->obtPosition().z - 2.5 };
					modeleMur->defOrientation(0, 0, 0);
					modelePorte->defOrientation(0, 0, 0);
					modeleMur->defOrientation(0, (*it).rotation, 0);
					modelePorte->defOrientation(0, -(*it).rotation, 0);
					modeleMur->defPosition(vecteurMur);
					modelePorte->defPosition(vecteurMur.x - 1.0, vecteurMur.y, vecteurMur.z);
					break;
				case -90:
					vecteur = { modeleporte->obtPosition().x + 0.5, modeleporte->obtPosition().y, modeleporte->obtPosition().z + 1.2 };
					joueur.defPosition(modeleporte->obtPosition());
					vecteurMur = { modeleporte->obtPosition().x, modeleporte->obtPosition().y, modeleporte->obtPosition().z + 2.5 };
					modeleMur->defOrientation(0, 0, 0);
					modelePorte->defOrientation(0, 0, 0);
					modeleMur->defOrientation(0, (*it).rotation, 0);
					modelePorte->defOrientation(0, -(*it).rotation, 0);
					modeleMur->defPosition(vecteurMur);
					modelePorte->defPosition(vecteurMur.x + 1.0, vecteurMur.y, vecteurMur.z);
					break;
				case 180:
					vecteur = { modeleporte->obtPosition().x - 1.2, modeleporte->obtPosition().y, modeleporte->obtPosition().z + 0.5 };
					joueur.defPosition(modeleporte->obtPosition());
					vecteurMur = { modeleporte->obtPosition().x - 2.5, modeleporte->obtPosition().y, modeleporte->obtPosition().z };
					modeleMur->defOrientation(0, 0, 0);
					modelePorte->defOrientation(0, 0, 0);
					modeleMur->defOrientation(0, (*it).rotation, 0);
					modelePorte->defOrientation(0, (*it).rotation - 180, 0);
					modeleMur->defPosition(vecteurMur);
					modelePorte->defPosition(vecteurMur.x, vecteurMur.y, vecteurMur.z + 1.0);
					break;
				}
				joueur.defPosition(vecteur);
			}
			++it;
		}
	}

	void creer(const unsigned int limite){
		carte.creer(limite);
		int itterateurPorte(0);

		int* porte = new int[limite];
		Entree entree;
		Sortie sortie;
		for (unsigned int i = 0; i < limite; ++i)
			porte[i] = 0;

		for (unsigned int i = 0; i < limite; ++i){
			itterateurPorte = 0;
			for (unsigned int j = 0; j < limite; ++j){
				if (carte.matrice[i * limite + j]){
					entree = std::make_tuple(i, itterateurPorte++, false);
					sortie = std::make_tuple(j, porte[j]);
					++porte[j];
					ajouterLien(entree, sortie);

				}
			}
		}

		std::ifstream fichierSalle("salle_text.txt");
		std::ifstream fichierObjet("objet_text.txt");

		std::string curseur1, curseur2, curseur3;
		int itterateur(0);
		while (!fichierSalle.eof()) {
			fichierSalle >> curseur1; fichierSalle >> curseur2; fichierSalle >> curseur3;
			cheminsModeleText.push_back(std::make_tuple(curseur1, curseur2, curseur3));
			++itterateur;
		}

		int aleatoire;
		int ID(0), pos;
		double x(0), y(0), z(0), xMin, xMax, yMin, yMax, zMin, zMax;
		std::list<BoiteCollision<double>> boiteObjet;
		Vecteur3d pos3D(0, 0, 0);
		InfoObjet objet;
		bool boPorte;
		for (unsigned int i = 0; i < limite; ++i){
			InfoSalle salle;
			salle.ID = i;
			salle.nbrPorte = carte.degreSortant(i);
			salle.echelle = { rand() % 3 + 2.0, 2, rand() % 3 + 2.0 };
			//aleatoire = rand() % itterateur;
			aleatoire = /*rand() % 2*/0; // en attendant que toutes eles salles sont conformes
			salle.cheminModele = (char*)(std::get<0>(cheminsModeleText[aleatoire])).c_str();
			salle.cheminTexture = (char*)(std::get<1>(cheminsModeleText[aleatoire])).c_str();
			LecteurFichier::lireBoite((char*)(std::get<2>(cheminsModeleText[aleatoire])).c_str(), salle);
			boiteObjet = std::list<BoiteCollision<double>>();
			for (unsigned short IDPorte = 0; IDPorte < /*salle.nbrPorte*/8; ++IDPorte) {
				objet.ID = IDPorte;
				objet.cheminModele = "portePlate.obj";// "HARDCODÉ"
				objet.cheminTexture = "portePlate.png";// "HARDCODÉ"
				boPorte = false;
				while (!boPorte) {
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
					x = abs(xMax - xMin);
					do{
						yMin = (*it).obtBoite()[rand() % 8].y;
						yMax = (*it).obtBoite()[rand() % 8].y;
					} while (yMin == yMax);
					if (yMax < yMin){
						y = yMin;
						yMin = yMax;
						yMax = y;
					}
					y = abs(yMax - yMin);
					do{
						zMin = (*it).obtBoite()[rand() % 8].z;
						zMax = (*it).obtBoite()[rand() % 8].z;
					} while (zMin == zMax);
					if (zMax < zMin){
						z = zMin;
						zMin = zMax;
						zMax = z;
					}
					z = abs(zMax - zMin);

					xMin += 0.25;
					xMax -= 0.25;
					zMin += 0.25;
					zMax -= 0.25;

					switch (rand() % 4) {
					case 0:
						objet.direction = { 1, 0, 0 };
						objet.rotation = 180;
						--zMax;
						break;
					case 1:
						objet.direction = { -1, 0, 0 };
						objet.rotation = 0;
						++zMin;
						break;
					case 2:
						objet.direction = { 0, 0, 1 };
						objet.rotation = 90;
						++xMin;
						break;
					case 3:
						objet.direction = { 0, 0, -1 };
						objet.rotation = -90;
						--xMax;
						break;
					}

					pos3D.y = yMin;

					do {
						pos3D.x = xMin + rand() % (int)(xMax - xMin);
					} while (pos3D.x < xMin);

					do {
						pos3D.z = zMin + rand() % (int)(zMax - zMin);
					} while (pos3D.z < zMin);

					for (auto it : salle.Objet) {
						if (objet.direction == it.direction) {
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


				boiteObjet.push_back(LecteurFichier::lireBoiteObjet("Porte.txt"));// "HARDCODÉ"

				objet.position = pos3D;
				salle.Objet.push_back(objet);
			}
			infosSalles.push_back(salle);
		}

		auto debut = infosSalles.begin();
		pos = rand() % infosSalles.size();
		std::advance(debut, pos);

		salleActive = new Salle(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele((*debut).cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture((*debut).cheminTexture)), (*debut).nbrPorte, (*debut).ID);
		salleActive->defEchelle((*debut).echelle);
		for (auto it : (*debut).Objet) {
			gfx::Modele3D* modeleporte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(it.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(it.cheminTexture));
			modeleporte->defPosition(it.position);
			modeleporte->defOrientation(0, it.rotation, 0);

			Objet* porte = new Porte(modeleporte, it.ID, "Metal", it.position, { 0, 0, 0 }, false, true, false, false);
			porte->defVitesse(it.direction);
			porte->defPosition(Vecteur3d(porte->obtPosition().x, porte->obtPosition().y + 0.2, porte->obtPosition().z));
			while (!Physique::obtInstance().collisionObjetSalle(salleActive, *porte, false)) {
				porte->defPosition(porte->obtPosition() + (it.direction / 10));
			}
			porte->defPosition(Vecteur3d(porte->obtPosition().x, porte->obtPosition().y - 0.2, porte->obtPosition().z));

			salleActive->ajoutObjet(porte);
		}
		modeleMur = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("murSalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("murSalle.png"));
		modelePorte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("portePlate.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("portePlate.png"));
		modeleMur->defOrientation(0, 0, 0);
		modelePorte->defOrientation(0, 0, 0);
	}
};
