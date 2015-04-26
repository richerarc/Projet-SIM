#pragma once
#include "Singleton.h"
#include <map>
#include <iostream>
#include <fstream>

enum Action {
	AVANCER,RECULER,DROITE,GAUCHE,SAUTER,ACCROUPIR,COURIR,TIRER,UTILISER,INVENTAIRE
};

class GestionnaireControle: public Singleton<GestionnaireControle> {
private:
	std::map<int, int> Controles;
	
public:
	void lireControle(char* Emplacement) {
		char Evenement[3];
		char Touche[13];
		std::ifstream FichierDeLecture(Emplacement);
		if (FichierDeLecture.is_open()) {
			while (!FichierDeLecture.eof()) {
				FichierDeLecture >> Evenement;
				FichierDeLecture >> Touche;
				int EvenementEnInt = std::atoi(Evenement);
				int ToucheEnInt = std::atoi(Touche);

				switch (EvenementEnInt) {
				case 0:
					Controles[AVANCER] = ToucheEnInt;
					break;
				case 1:
					Controles[RECULER] = ToucheEnInt;
					break;
				case 2:
					Controles[DROITE] = ToucheEnInt;
					break;
				case 3:
					Controles[GAUCHE] = ToucheEnInt;
					break;
				case 4:
					Controles[SAUTER] = ToucheEnInt;
					break;
				case 5:
					Controles[ACCROUPIR] = ToucheEnInt;
					break;
				case 6:
					Controles[COURIR] = ToucheEnInt;
					break;
				case 7:
					Controles[TIRER] = ToucheEnInt;
					break;
				case 8:
					Controles[UTILISER] = ToucheEnInt;
					break;
				case 9:
					Controles[INVENTAIRE] = ToucheEnInt;
					break;
				}
				

					
			}

		}
	}
	bool definirControle(Action Evenement, int Controle) {
		
		for (std::map<int, int>::iterator it = Controles.begin(); it != Controles.end(); ++it) {
			if (it->second == Controle)
				return false;
			
		}
		
		Controles[Evenement] = Controle;
		return true;
		
		
	}

	void sauvegarderControle(char* Emplacement) {
		std::ofstream EcritureFichier(Emplacement);

		EcritureFichier << "0" << std::endl;
		EcritureFichier << Controles[AVANCER] << std::endl;

		EcritureFichier << "1" << std::endl;
		EcritureFichier << Controles[RECULER] << std::endl;

		EcritureFichier << "2" << std::endl;
		EcritureFichier << Controles[DROITE] << std::endl;

		EcritureFichier << "3" << std::endl;
		EcritureFichier << Controles[GAUCHE] << std::endl;

		EcritureFichier << "4" << std::endl;
		EcritureFichier << Controles[SAUTER] << std::endl;

		EcritureFichier << "5" << std::endl;
		EcritureFichier << Controles[ACCROUPIR] << std::endl;

		EcritureFichier << "6" << std::endl;
		EcritureFichier << Controles[COURIR] << std::endl;

		EcritureFichier << "7" << std::endl;
		EcritureFichier << Controles[TIRER] << std::endl;

		EcritureFichier << "8" << std::endl;
		EcritureFichier << Controles[UTILISER] << std::endl;

		EcritureFichier << "9" << std::endl;
		EcritureFichier << Controles[INVENTAIRE];


	}

	std::map<int,int> obtenirControles(void) {
		return Controles;
	}

	std::string* obtTouche(Action action) {
		std::string* str;
		char touche = Controles[action];

		switch (Controles[action]) {

		case 1073742049:
			str = new std::string("LSHIFT");
			break;

		default:
			switch (touche) {
			case 32:
				str = new std::string("SPACE");
				break;

			case 9:
				str = new std::string("TAB");
				break;

			default:
				char * chr = new char(touche);
				str = new std::string(chr);

				int i = 0;
				while (chr[i] > 0)
					++i;
				str->erase(i, str->length());
				break;
			}
			break;
		}
		return str;
	}

};