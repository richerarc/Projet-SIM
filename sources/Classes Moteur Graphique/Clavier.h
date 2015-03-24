#pragma once

#include <set>

class Clavier {
public:
	static void mettreAJourEtat(short touche, bool etat){
		if (etat)
			touches.insert(touche);
		else
			touches.erase(touche);
	}

	static bool toucheAppuyee(short touche){
		return touches.find(touche) != touches.end();
	}

	static bool toucheRelachee(short touche){
		return !(touches.find(touche) != touches.end());
	}
private:
	static std::set<short> touches;
};
std::set<short> Clavier::touches;