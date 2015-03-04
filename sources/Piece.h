#pragma once
#include "Contenu.h"

class Piece{
private:
	std::list</**Objet*/> objets;
	float valeurProb;
	/*Obstacle obstacle;*/

public:
	Piece(){
		//Pas trop sur yo
	}

	void ajoutObjet(*Objet Objet){ // Objet thingy
		objets.push_back(Objet);
	}

	Objet obtObjet(unsigned int position,bool effacer){ //Permet soir d'obtenir l'objet ou de le retirer/supprimer de la liste.
		if (!effacer)
			return objets[position];
		else{
			objets[position].erase;
			return 0;
		}	
	}

	void modiProb(float prob){
		valeurProb = prob;
	}

	float obtValeurProb(){
		return valeurProb;
	}

	/*Obstacle*/
};