#pragma once
#include "Salle.h"
#include "Objet.h"

class Piece : public Salle{
private:
	std::list<Objet*> objets;
	float valeurProb;

public:
	Piece(){}
	
	Piece(gfx::Modele3D modele, unsigned int nbrPortes, int ID) : Salle(modele, nbrPortes, ID){
		
	}

	void ajoutObjet(Objet *objet){
		objets.push_back(objet);
	}

	Objet* obtObjet(unsigned int ID){
		for(auto it: objets){
			if (it->obtID() == ID)
				return it;
		}
	}

	void modiProb(float prob){
		valeurProb = prob;
	}

	float obtValeurProb(){
		return valeurProb;
	}

	std::list<Objet*>& obtListeObjet() {

		return objets;
	}
};