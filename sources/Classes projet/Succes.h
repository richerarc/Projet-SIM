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
	~Succes(){
		if (titre != nullptr)
			delete titre;
		if (description != nullptr)
		    delete description;
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