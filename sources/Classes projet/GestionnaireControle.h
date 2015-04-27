#pragma once
#include "Singleton.h"
#include <map>
#include <iostream>
#include <fstream>

enum Action {
	AVANCER,RECULER,DROITE,GAUCHE,SAUTER,ACCROUPIR,COURIR,TIRER,UTILISER,INVENTAIRE
};

enum Controleur_t {CLAVIER = 0, SOURIS = 1, MANETTE = 2};

typedef std::tuple<Action, Controleur_t> ClefControle;

ClefControle cle(Action action, int ctrl){
	return std::make_tuple(action, (Controleur_t)ctrl);
}

class GestionnaireControle: public Singleton<GestionnaireControle> {
private:
	
	std::map<ClefControle, int> controles;
	
public:
	void lireControle(char* Emplacement) {
		char evenement[3];
		char touche[13];
		char controleur[13];
		std::ifstream FichierDeLecture(Emplacement);
		if (FichierDeLecture.is_open()) {
			while (!FichierDeLecture.eof()) {
				FichierDeLecture >> evenement;
				FichierDeLecture >> controleur;
				FichierDeLecture >> touche;
				int evenementEnInt = std::atoi(evenement);
				int controleurEnInt = SDL_atoi(controleur);
				int toucheEnInt = std::atoi(touche);
				
				

				switch (evenementEnInt) {
				case 0:
						controles[cle(AVANCER, controleurEnInt)] = toucheEnInt;
					break;
				case 1:
					controles[cle(RECULER, controleurEnInt)] = toucheEnInt;
					break;
				case 2:
					controles[cle(DROITE, controleurEnInt)] = toucheEnInt;
					break;
				case 3:
					controles[cle(GAUCHE, controleurEnInt)] = toucheEnInt;
					break;
				case 4:
					controles[cle(SAUTER, controleurEnInt)] = toucheEnInt;
					break;
				case 5:
					controles[cle(ACCROUPIR, controleurEnInt)] = toucheEnInt;
					break;
				case 6:
					controles[cle(COURIR, controleurEnInt)] = toucheEnInt;
					break;
				case 7:
					controles[cle(TIRER, controleurEnInt)] = toucheEnInt;
					break;
				case 8:
					controles[cle(UTILISER, controleurEnInt)] = toucheEnInt;
					break;
				case 9:
					controles[cle(INVENTAIRE, controleurEnInt)] = toucheEnInt;
					break;
				}
				

					
			}

		}
	}
	bool definirControle(Action evenement, Controleur_t controleur, int controle) {
		
		for (std::map<ClefControle, int>::iterator it = controles.begin(); it != controles.end(); ++it) {
			if (it->second == controle)
				return false;
		}
		controles[cle(evenement, controleur)] = controle;
		return true;
	}

	void sauvegarderControle(char* emplacement) {
		std::ofstream ecritureFichier(emplacement);
		
		char num = '0';
		for (auto it : controles){
			ecritureFichier << num << std::endl;
			ecritureFichier << std::get<1>(it.first) << std::endl;
			ecritureFichier << it.second << std::endl;
			++num;
		}

	}

	std::map<ClefControle, int> obtenirControles(void) {
		return controles;
	}

	std::string* obtTouche(Action action) {
		Controleur_t controleur;
		for (auto it : controles ){
			if (std::get<0>(it.first) == action){
				controleur = std::get<1>(it.first);
				break;
			}
		}
		
		std::string* str;
		
		ClefControle cle = std::make_tuple(action,controleur);
		
		if (controleur == CLAVIER){
			char touche = controles[cle];
			
			switch (controles[cle]) {
					
				case 1073742049:
					str = new std::string("LSHIFT");
					break;
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
		}
		else if (controleur == SOURIS){
			switch (controles[cle]) {
				case 0:
					str = new std::string("LEFT MB");
					break;
				case 1:
					str = new std::string("MIDDLE MB");
					break;
				case 2:
					str = new std::string("RIGHT MB");
					break;
			}
		}
		else if (controleur == MANETTE){
			switch (controles[cle]) {
				default:
					break;
			}
		}
			
		return str;
	}

};