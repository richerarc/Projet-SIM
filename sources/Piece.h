#pragma once
#include "Salle"
#include "Contenu.h"

class Piece : public Salle{
private:
	std::list<Objet*> objets;
	float valeurProb;
	Obstacle obstacle;

public:
	Piece(){}
	
	Piece(Vecteur3d Pos, Obstacle obstacle, Modele3D modele) : public Salle(Pos, modele){
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
	
	void defObstacle(Obstacle obstacle){
		this->obstacle = obstacle;
	}

	Obstacle obtObstacle(){
		return this->obstacle;
	}
};