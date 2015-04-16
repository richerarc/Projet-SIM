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
#include "LecteurFichier.h"

typedef std::tuple<unsigned int, unsigned int, bool> Entree;
typedef std::tuple<unsigned int, unsigned int> Sortie;
typedef std::tuple<std::string, std::string, std::string> Modele_Text;

class Carte : public Singleton < Carte > {
private:
	graphe::Graphe carte;
	std::map<Entree, Sortie> liens;
	std::list<InfoSalle> infosSalles;

	std::vector<Modele_Text> cheminsModeleText;

	void ajouterLien(Entree entree, Sortie sortie){
		liens[entree] = sortie;
	}

	unsigned short aleatoire4Bit(unsigned short banqueDeBit){
		switch (banqueDeBit){
		case(1) :
			return banqueDeBit;
		case(2) :
			return banqueDeBit;
		case(4) :
			return banqueDeBit;
		case(8) :
			return banqueDeBit;
		default:
			unsigned short renvoi;
			do{
				renvoi = 1 << (rand() % 4);
			} while (banqueDeBit & renvoi != renvoi);
			return renvoi;
		}
	}
public:

	Salle *salleActive;

	std::tuple<unsigned int, unsigned int> destination(std::tuple<unsigned int, unsigned int, bool> sortie){
		return liens[sortie];
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
			for (unsigned int j = 0; j < limite; ++j){
				if (carte.matrice[i * limite + j]){
					entree = std::make_tuple(i, ++itterateurPorte, false);
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
		unsigned short directions; // x>0 = 1 , x<0 = 2 , z>0 = 4 , z<0 = 8
		double x(0), y(0), z(0), xMin, xMax, yMin, yMax, zMin, zMax;
		std::list<BoiteCollision<double>> boiteObjet;
		Vecteur3d pos3D(0, 0, 0);
		InfoObjet objet;
		bool boPorte;
		for (unsigned int i = 0; i < limite; ++i){
			InfoSalle salle;
			salle.ID = i;
			salle.nbrPorte = carte.degreSortant(i);
			//aleatoire = rand() % itterateur;
			aleatoire = /*rand() % 2*/1; // en attendant que toutes eles salles sont conformes
			salle.cheminModele = (char*)(std::get<0>(cheminsModeleText[aleatoire])).c_str();
			salle.cheminTexture = (char*)(std::get<1>(cheminsModeleText[aleatoire])).c_str();
			LecteurFichier::lireBoite((char*)(std::get<2>(cheminsModeleText[aleatoire])).c_str(), salle);
			boiteObjet =  std::list<BoiteCollision<double>>();
			for (unsigned short IDPorte = 0; IDPorte < 4/*salle.nbrPorte*/; ++IDPorte){
				objet.ID = IDPorte;
				objet.cheminModele = "portePlate.obj";// "HARDCODÉ"
				objet.cheminTexture = "portePlate1.png";// "HARDCODÉ"
				boPorte = false;
				while (!boPorte) {
					boPorte = true;
					do{
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

						directions = 0;
						for (auto boite : salle.boitesCollision) {
							for (short j = 0; j < 8; ++j){
								if (j != pos){
									if ((((boite).obtBoite()[j].x >= xMax) && ((directions & 1) != 1)))
										directions += 1;
									if ((((boite).obtBoite()[j].x <= xMin) && ((directions & 2) != 2)))
										directions += 2;
									if ((((boite).obtBoite()[j].z >= zMax) && ((directions & 4) != 4)))
										directions += 4;
									if ((((boite).obtBoite()[j].z <= zMin) && ((directions & 8) != 8)))
										directions += 8;
								}
							}
						}
					} while (directions == 0);

					pos3D.y = yMin;
					switch (aleatoire4Bit(65535 - (~directions))){
					case(1) :
						pos3D.x = xMax; pos3D.z = (z) / 2 + zMin;
						objet.rotation = 180;
						break;
					case(2) :
						pos3D.x = xMin; pos3D.z = (z) / 2 + zMin;
						objet.rotation = 0;
						break;
					case(4) :
						pos3D.x = (x) / 2 - xMax; pos3D.z = zMax;
						objet.rotation = 90;
						break;
					case(8) :
						pos3D.x = (x) / 2 + xMin; pos3D.z = zMin;
						objet.rotation = -90;
						break;
					}

					for (auto it : salle.Objet) {
						if (pos3D == it.position)
							boPorte = false;
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
		for (auto it : (*debut).Objet) {
			gfx::Modele3D* modeleporte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(it.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(it.cheminTexture));
			modeleporte->defEchelle(3, 3, 3);
			modeleporte->defPosition(it.position);
			modeleporte->defOrientation(0, it.rotation, 0);
			salleActive->ajoutObjet(new Porte(modeleporte, it.ID, "Metal", it.position, { 0, 0, 0 }, false, true, false, false));
		}
	}
};
