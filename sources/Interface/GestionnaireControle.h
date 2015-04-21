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

	char* obtToucheControleEnChar(int toucheEnInt){
		switch (toucheEnInt){
		case (SDLK_q) :
			return "Q";
			break;
		case (SDLK_w) :
			return "W";
			break;
		case (SDLK_e) :
			return "E";
			break;
		case (SDLK_r) :
			return "R";
			break;
		case (SDLK_t) :
			return "T";
			break;
		case (SDLK_y) :
			return "Y";
			break;
		case (SDLK_u) :
			return "U";
			break;
		case (SDLK_i) :
			return "I";
			break;
		case (SDLK_o) :
			return "O";
			break;
		case (SDLK_p) :
			return "P";
			break;
		case (SDLK_a) :
			return "A";
			break;
		case (SDLK_s) :
			return "S";
			break;
		case (SDLK_d) :
			return "D";
			break;
		case (SDLK_f) :
			return "F";
			break;
		case (SDLK_g) :
			return "G";
			break;
		case (SDLK_h) :
			return "H";
			break;
		case (SDLK_j) :
			return "J";
			break;
		case (SDLK_k) :
			return "K";
			break;
		case (SDLK_l) :
			return "L";
			break;
		case (SDLK_z) :
			return "Z";
			break;
		case (SDLK_x) :
			return "X";
			break;
		case (SDLK_c) :
			return "C";
			break;
		case (SDLK_v) :
			return "V";
			break;
		case (SDLK_b) :
			return "B";
			break;
		case (SDLK_n) :
			return "N";
			break;
		case (SDLK_m) :
			return "M";
			break;

		case (SDLK_BACKSPACE) :
			return "Backspace";
			break;
		case (SDLK_SPACE) :
			return "Space";
			break;
		}
	}

};