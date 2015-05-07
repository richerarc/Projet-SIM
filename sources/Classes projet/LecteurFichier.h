#pragma once

#include "Info.h"
#include "BoiteCollision.h"
#include <fstream>

namespace LecteurFichier{
	bool lireBoite(char* cheminAcces, InfoSalle& salle){
		std::ifstream fichier(cheminAcces);

		if (fichier.is_open()){

			char* ligne = new char();
			Vecteur3d tabBoite[8];

			while (!fichier.eof()){
				fichier >> ligne;
				for (int i = 0; i < 8; ++i){
					fichier >> tabBoite[i].x >> tabBoite[i].y >> tabBoite[i].z;
					tabBoite[i] *= salle.echelle;
				}
				salle.boitesCollision.push_back(tabBoite);
				fichier >> ligne;
			}
			fichier.close();
		}
		return false;
	}

	BoiteCollision<double> lireBoiteObjet(char* cheminAcces){
		std::ifstream fichier(cheminAcces);
		char* ligne = new char();
		Vecteur3<double> tabBoite[8];
		double x, y, z;

		fichier.getline(ligne, 256);

		for (int i = 0; i < 8; ++i){
			fichier >> x >> y >> z;
			tabBoite[i] = Vecteur3<double>(x * 2, y * 2, z * 2);
		}

		BoiteCollision<double> boite(tabBoite);
		fichier.close();
		return boite;
	}

	bool lireObjet(const char* cheminAcces, InfoObjet &info) {
		std::ifstream fichier(cheminAcces);

		if (fichier.is_open()) {
			char *cheminOBJ = new char();
			char *cheminTEXTURE = new char();
			int type;
			fichier >> cheminOBJ >> cheminTEXTURE >> type;
			info.cheminModele = cheminOBJ;
			info.cheminTexture = cheminTEXTURE;
			info.type = type;
			return true;
		}
		return false;
	}

	bool lirePuzzle(const char* cheminAcces, InfoPuzzle &info){
		std::ifstream fichier(cheminAcces);

		if (fichier.is_open()){

			double x, y, z;
			char* ligne = new char();
			char* cheminObjet = new char();
			Vecteur3d tabBoite[8];
			bool tabEntrees[4];

			while (!fichier.eof()){
				fichier.getline(ligne, 256);
				if (!strcmp(ligne, "puzzle{")){
					fichier.getline(ligne, 256);
					while (strcmp(ligne, "};")){
						if (!strcmp(ligne, "boite{")){
							for (int i = 0; i < 8; ++i){
								fichier >> x >> y >> z;
								tabBoite[i] = Vecteur3d(x, y, z);
							}
							info.boiteCollision = BoiteCollision<double>(tabBoite);
							fichier.getline(ligne, 256);
						}
						if (!strcmp(ligne, "entrees{")) {
							for (int i = 0; i < 4; ++i) {
								fichier >> x;
								tabEntrees[i] = x;
							}
							info.entrees = tabEntrees;
							fichier.getline(ligne, 256);
						}
						if (!strcmp(ligne, "objet{")){
							InfoObjet objet;
							fichier >> ligne >> cheminObjet;
							if (!strcmp(ligne, "c")){
								lireObjet(cheminObjet, objet);
							}
							fichier >> ligne >> x >> y >> z;
							if (!strcmp(ligne, "p")){
								objet.position = Vecteur3d(x, y, z);
							}
							info.objet.push_back(objet);
							fichier.getline(ligne, 256);
						}
						fichier.getline(ligne, 256);
					}
				}
			}
			fichier.close();
		}

		return false;
	}
}