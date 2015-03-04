#include <list>

class Piece{
private:
	std::list</**Objet*/> objets;
	float valeurProb;
	/*Obstacle obstacle;*/

public:
	Piece(){
		//Pas trop sur yo
	}

	void ajouterObjet(*Objet Objet){ // Objet thingy
		objets.push_back(Objet);
	}

	Objet obtenirObjet(unsigned int position,bool effacer){ //Permet soir d'obtenir l'objet ou de le retirer/supprimer de la liste.
		if (!effacer)
			return objets[position];
		else{
			objets[position].erase;
			return 0;
		}	
	}

	void modifierProb(float prob){
		valeurProb = prob;
	}

	float obtenirValeurProb(){
		return valeurProb;
	}

	/*Obstacle*/
};