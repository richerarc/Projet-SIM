#pragma once
#include "Salle"
#include "Contenu.h"

class Piece : public Salle{
private:
	std::list<Objet*> objets;
	float valeurProb;

public:
	Piece(){}
	
	Piece(Modele3D modele, int ID) : public Salle(modele, ID){
		this->obstacle = obstacle;
	}

	void ajoutObjet(Objet *objet){
		objets.push_back(objet);
	}

	Objet* obtObjet(unsigned int ID){
		for(auto it: objets){
			if(it->ID == ID)
				return it
		}
	}

	void modiProb(float prob){
		valeurProb = prob;
	}

	float obtValeurProb(){
		return valeurProb;
	}
};