#pragma once 
#include <vector>

#include "Case.h"
#include "Vecteur2.h"
class Inventaire{
private:
	std::vector<Case*> sacADos;
	std::vector<Case*> menuAccesRapide;
public:
	Inventaire(Vecteur2f taille){
		for (int i = 0; i < taille.x * taille.y; ++i){
			if (i < taille.x)
				menuAccesRapide.push_back(new Case());
			sacADos.push_back(new Case());
		}
	}
	~Inventaire(){
		while (sacADos.size() > 0){
			delete sacADos.back();
			sacADos.pop_back();
		}
		while (menuAccesRapide.size() > 0){
			delete menuAccesRapide.back();
			menuAccesRapide.pop_back();
		}
	}

	bool ajouterObjet(InfoObjet *objet){
		//Vérifions si il reste de la place dans le menu d'accès rapide
		for (Case* i : menuAccesRapide){
			if (i->obtObjet() == nullptr){
				i->defObjet(objet);
				return true;
			}
		}
		//Sinon, regardons pour le sac à dos.
		for (Case* i : sacADos){
			if (i->obtObjet() == nullptr){
				i->defObjet(objet);
				return true;
			}
		}
		return false;
	}

	InfoObjet* ajouterObjetCaseSacADos(InfoObjet *objet, int position){
		if (! position < sacADos.size())
			return nullptr;
		InfoObjet* tmp = sacADos[position]->retirerObjet();
		sacADos[position]->defObjet(objet);
		return tmp;
	}

	InfoObjet* ajouterObjetCaseAccesRapide(InfoObjet *objet, int position){
		if (!position < menuAccesRapide.size())
			return nullptr;
		InfoObjet* tmp = menuAccesRapide[position]->retirerObjet();
		menuAccesRapide[position]->defObjet(objet);
		return tmp;
	}

	InfoObjet* retirerObjetSacADos(int position){
		return sacADos[position]->retirerObjet();
	}

	InfoObjet* retirerObjetAccesRapide(int position){
		return menuAccesRapide[position]->retirerObjet();
	}

	InfoObjet* obtObjetSacADos(int position){
		return sacADos[position]->obtObjet();
	}

	InfoObjet* obtObjetAccesRapide(int position){
		return sacADos[position]->obtObjet();
	}
};