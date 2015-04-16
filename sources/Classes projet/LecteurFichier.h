#pragma once

#include "Info.h"
#include "BoiteCollision.h"
#include <fstream>

namespace LecteurFichier{
	bool lireBoite(char* cheminAcces, InfoSalle& salle){
		std::ifstream fichier(cheminAcces);
		if (fichier.is_open()){

			char* ligne = new char();
			Vecteur3<double> tabBoite[8];
			double x, y, z;
			while (!fichier.eof()){
				fichier.getline(ligne, 256);
				for (int i = 0; i < 8; ++i){
					fichier >> x >> y >> z;
					tabBoite[i] = Vecteur3<double>(x * 3, y * 3, z * 3);
				}
				BoiteCollision<double> boite(tabBoite);
				salle.boitesCollision.push_back(boite);
				fichier.getline(ligne, 256);
				fichier.getline(ligne, 256);
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
			tabBoite[i] = Vecteur3<double>(x * 3, y * 3, z * 3);
		}
		BoiteCollision<double> boite(tabBoite);
		fichier.close();
		return boite;
	}


	bool lirePuzzle(char* cheminAcces){
		std::ifstream fichier(cheminAcces);
		/*Exemple fichier
		...
		Puzzle{
		x y z//dimension max
		Objet{
		c \FichierObjet
		s x y z//position, objet au sol
		o x y z//orientation
		}
		Objet{
		c \FichierObjet
		m x y z//position, objet au mur
		o x y z//orientation
		}
		};
		...
		*/
		if (fichier.is_open()){

			char* ligne = new char();

			while (!fichier.eof()){
				fichier.getline(ligne, 256);
				if (ligne == "Puzzle{"){
					double x, y, z;
					fichier >> x >> y >> z;
					Vecteur3<double> dimension(x, y, z);
					Vecteur3<double> *position, *orientation;
					char* cheminObjet = new char();
					fichier.getline(ligne, 256);
					while (ligne != "};"){
						if (ligne == "Objet{"){
							fichier >> ligne >> cheminObjet;
							fichier >> ligne >> x >> y >> z;
							position = new Vecteur3<double>(x, y, z);
							if (ligne == "m"){
								//à coder
								fichier >> ligne >> x >> y >> z;
								orientation = new Vecteur3<double>(x, y, z);
							}
							else if (ligne == "s"){
								//à coder
								fichier >> ligne >> x >> y >> z;
								orientation = new Vecteur3<double>(x, y, z);
							}
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