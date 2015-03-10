#pragma once
#include "Vecteur3.h"
//Note à moi-même: AfficherTexture vs AfficherTexte
class Objet2D{
private:
	Vecteur3f position; 
	Vecteur3f orientation;
	Vecteur3f origine;
	Vecteur3i echelle;
	SDL_Surface* surface;
public:
	Objet2D(Vecteur3f position){
		this->position = position;
	}
	void afficher(){
	
	}

};