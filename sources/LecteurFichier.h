#pragma once
#include "BoiteCollision.h"
#include "Salle.h"
#include <fstream>

namespace LecteurFichier{
	bool lireBoite(char* cheminAcces, Salle& salle){
		std::ifstream fichier("cheminAcces");
		
		if (fichier.is_open()){ 

			char* ligne;

			while (!fichier.eof()){
				fichier >> ligne;
				if (ligne == "Boite{"){
					Vecteur3<double> boite[8];
					double x, y, z;
					for (int i = 0; i < 8; i++){
						fichier >> x >> y >> z;
						boite[i] = Vecteur3<double>(x, y, z);
					}
				}
			}

			fichier.close();
		}

		else
			return false;
	}


	bool lirePuzzle(){ return false; } // à implémenter plus tard
}

