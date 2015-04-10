#pragma once
#include <map>
#include <tuple>
#include <list>
#include <vector>
#include <fstream>
#include "Modele3D.h"
#include "Porte.h"
#include "Salle.h"
#include "Info.h"
#include "Graphe.h"
#include "GestionnaireChemin.h"
#include "LecteurFichier.h"

typedef std::tuple<unsigned int, unsigned int, bool> Entree;
typedef std::tuple<unsigned int, unsigned int> Sortie;
typedef std::tuple<char*, char*, char*> Modele_Text;

class Carte : public Singleton < Carte > {
private:
	graphe::Graphe carte;
	std::map<Entree, Sortie> liens;
	std::list<InfoSalle> infosSalles;

	std::vector<Modele_Text> cheminsModeleText;

	void ajouterLien(Entree entree, Sortie sortie){
		liens[entree] = sortie;
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

		char* curseur1, *curseur2, *curseur3;
		int itterateur(1);
		while (!fichierSalle.eof()) {
			fichierSalle >> curseur1; fichierSalle >> curseur2; fichierSalle >> curseur3;
			cheminsModeleText.push_back(std::make_tuple(curseur1, curseur2, curseur3));
			++itterateur;
		}

		InfoSalle salle;
		int aleatoire;
		int ID(0), pos;
		double x(0), y(0), z(0), xMin, xMax, yMin, yMax, zMin, zMax;
		std::list<BoiteCollision<double>> boiteObjet;
		Vecteur3d pos(0,0,0);

		for (unsigned int i = 0; i < limite; ++i){
			salle.ID = i;
			salle.nbrPorte = carte.degreSortant(i);
			aleatoire = rand() % itterateur;
			salle.cheminModele = std::get<0>(cheminsModeleText[aleatoire]);
			salle.cheminTexture = std::get<1>(cheminsModeleText[aleatoire]);
			LecteurFichier::lireBoite(std::get<2>(cheminsModeleText[aleatoire]), salle);
			for (unsigned short IDPorte = 0; IDPorte < salle.nbrPorte; ++IDPorte){
				InfoObjet = objet;
				objet.ID = IDPorte;
				objet.cheminModele = "porte.obj";// "HARDCODÉ"
				objet.cheminTexture = "porte.png";// "HARDCODÉ"

				auto it = salle.boitesCollision.begin();
				pos = rand() % salle.boitesCollision.size;
				std::advance(it, pos);
				do{
					xMin = (*it).obtBoite[rand() % 8].x;
					xMax = (*it).obtBoite[rand() % 8].x;
				} while (xMin == xMax);
				if (xMax < xMin){
					x = xMin;
					xMin = xMax;
					xMax = x;
				}
				x = xMax - xMin;
				do{
					yMin = (*it).obtBoite[rand() % 8].y;
					yMax = (*it).obtBoite[rand() % 8].y;
				} while (yMin == yMax);
				if (yMax < yMin){
					y = yMin;
					yMin = yMax;
					yMax = y;
				}
				y = yMax - yMin;
				do{
					zMin = (*it).obtBoite[rand() % 8].z;
					zMax = (*it).obtBoite[rand() % 8].z;
				} while (zMin == zMax);
				if (zMax < zMin){
					z = zMin;
					zMin = zMax;
					zMax = z;
				}
				z = zMax - zMin;
				//Trouver les murs en regardant s'il y a d'autres boites à l'extérieur...
				if (pos > 1){
					//regarder en x et en z si il y a des boites qui on des coordonées passé le point.
				}
				pos.y = yMin;
				//4 possibilitées de positions
				//pos.x = xMin; pos.z = rand() % (zMax - zMin) + zMin;
				//pos.x = xMax; pos.z = rand() % (zMax - zMin) + zMin;
				//pos.x = rand() % (xMax - xMin) + xMin; pos.z = zMin;
				//pos.x = rand() % (xMax - xMin) + xMin; pos.z = zMax;


				boiteObjet.push_back(LecteurFichier::lireBoiteObjet("porte.txt"));// "HARDCODÉ"

				salle.Objet.push_back(objet);
			}
			infosSalles.push_back(salle);
		}


	}
};
