#include "Texte2D.h"

class Succes{
private:
	gfx::Texte2D* titre;
	gfx::Texte2D* description;
	bool accompli;
	unsigned short ID;
public:
	Succes(gfx::Texte2D* titre, gfx::Texte2D* description, unsigned short ID){
		this->titre = titre;
		this->description = description;
		this->accompli = false;
		this->ID = ID;
	}

	gfx::Texte2D* obtTitre(){
		return titre;
	}

	bool obtAccompli(){
		return accompli;
	}
	unsigned short obtID(){
		return ID;
	}
	gfx::Texte2D* obtDescription(){
		return description;
	}

	void defAccompli(bool accompli){
		this->accompli = accompli;
	}
};