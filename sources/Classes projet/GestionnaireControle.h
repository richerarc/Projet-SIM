#pragma once
#include "Singleton.h"
#include <map>
#include <iostream>
#include <fstream>

enum Action {
	AVANCER,RECULER,DROITE,GAUCHE,SAUTER,ACCROUPIR,COURIR,TIRER,UTILISER,ACCESINVENTAIRE
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
					controles[cle(ACCESINVENTAIRE, controleurEnInt)] = toucheEnInt;
					break;
				}
			}
		}
	}
	bool definirControle(Action evenement, Controleur_t controleur, int controle) {
		ClefControle clee = std::make_tuple(evenement, controleur);
		for (auto it : controles){
			if (std::get<0>(it.first) == evenement){
				controles.erase(cle(evenement, std::get<1>(it.first)));
				controles[clee] = controle;
				return true;
			}
		}
		return false;
	}

	void sauvegarderControle(char* emplacement) {
		std::ofstream ecritureFichier(emplacement);
		
		std::map<ClefControle, int>::iterator iterateur = controles.begin();

		char num = '0';
		for (auto it : controles){
			++iterateur;
			ecritureFichier << num << std::endl;
			ecritureFichier << std::get<1>(it.first) << std::endl;
			if (iterateur != controles.end())
				ecritureFichier << it.second << std::endl;
			else
				ecritureFichier << it.second;
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
		
		std::string* str = new std::string();
		
		ClefControle cle = std::make_tuple(action,controleur);
		
		if (controleur == CLAVIER){
			char touche = controles[cle];
			
			switch (controles[cle]) {
					
				case SDLK_LSHIFT:
					str->append("LSHIFT");
					break;

				case SDLK_RSHIFT:
					str->append("RSHIFT");
					break;

				case SDLK_SPACE:
					str->append("SPACE");
					break;

				case SDLK_TAB:
					str->append("TAB");
					break;

				case SDLK_UP:
					str->append("UP");
					break;

				case SDLK_DOWN:
					str->append("DOWN");
					break;

				case SDLK_LEFT:
					str->append("LEFT");
					break;

				case SDLK_RIGHT:
					str->append("RIGHT");
					break;

				case SDLK_LCTRL:
					str->append("LCTRL");
					break;

				case SDLK_RCTRL:
					str->append("RCTRL");
					break;

				default:
					char * chr = new char(touche);
					str->append(chr);
					
					int i = 0;
					while (chr[i] > 0)
						++i;
					str->erase(i, str->length());
					break;
			}
		}
		else if (controleur == SOURIS){
			switch (controles[cle]) {
				case 1:
					str->append("LEFT MB");
					break;
				case 2:
					str->append("MIDDLE MB");
					break;
				case 3:
					str->append("RIGHT MB");
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

	short touche(Action act){
		Controleur_t controleur;
		for (auto it : controles){
			if (std::get<0>(it.first) == act){
				controleur = std::get<1>(it.first);
				break;
			}
		}
		if (controleur == CLAVIER){
			return controles[std::make_tuple(act, controleur)];
		}
		return NULL;
	}

};
