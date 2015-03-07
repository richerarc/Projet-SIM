#pragma once
#include <set>

#include "Vecteur2.h"

class Souris
{
public:
	static void mettreAJourEtatBoutons(short bouton, bool etat){
		if (etat)
			boutons.insert(bouton);
		else
			boutons.erase(bouton);
	}

	static void mettreAJourEtatMolette(int x, int y){
		molette.x = x;
		molette.y = y;
	}

	static void mettreAJourPosition(int x, int y){
		position = Vecteur2f(x, y);
	}

	static bool boutonAppuye(short bouton){
		return boutons.find(bouton) != boutons.end();
	}

	static bool boutonRelache(short bouton){
		return boutons.find(bouton) == boutons.end();
	}

	static Vecteur2f obtPosition(){
		return position;
	}

	static Vecteur2f obtEtatMolette(){
		return molette;
	}
private:
	static std::set<short> boutons;
	static Vecteur2f position;
	static Vecteur2f molette;
};
}
