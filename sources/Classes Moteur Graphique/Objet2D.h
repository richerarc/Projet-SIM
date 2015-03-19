#pragma once
#include "Vecteur3.h"
#include "Vecteur2.h"
class Objet2D{
protected:
	Vecteur2f position;
	double orientation;
	Vecteur2f origine;
	Vecteur2f echelle;
	SDL_Surface* surface;
public:
	Objet2D(Vecteur2f position){
		this->position = position;
		echelle.x = 1;
		echelle.y = 1;

	}
	~Objet2D(){
		if (surface != nullptr){
			SDL_FreeSurface(surface);
			surface = nullptr;
		}
	}
	virtual void afficher() = 0;

	void defPosition(Vecteur2f position){
		this->position = position;
	}
	void deplacer(Vecteur2f position){
		this->position = this->position + position;
	}
	void defOrigine(Vecteur2f origine){
		this->origine = origine;
	}
	void defEchelle(Vecteur2f echelle){
		this->echelle = echelle;
		surface->h = surface->h*echelle.y;
		surface->w = surface->w*echelle.x;
	}
	void defOrientation(double orientation){
		this->orientation = orientation;
	}
	void rotationner(double orientation){
		this->orientation = this->orientation + orientation;
	}

	Vecteur2f obtPosition(){ return position; }
	Vecteur2f obtOrigine(){ return origine; }
	double obtOrientation(){ return orientation; }
	Vecteur2f obtEchelle(){ return echelle; }
};