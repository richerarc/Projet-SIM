#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Objet2D.h"
#include "Vecteur3.h"
//Note à moi-même : constructeur 
class Texte2D : public Objet2D{
public:
	std::string texte;
	std::string cheminPolice;
	unsigned int style;
	unsigned int taille;
	SDL_Color couleur;
	TTF_Font* police;

	Texte2D(Vecteur3f position, Vecteur3f orientation, Vecteur3f origine, Vecteur3i echelle) : Objet2D(position,orientation,origine,echelle){
	}

	~Texte2D(){
		TTF_CloseFont(police);
	}

	void defTexte(std::string texte){
		this->texte = texte;
	}
	void defPolice(const char* pathPolice){
		police = TTF_OpenFont(pathPolice, taille);
	}
	void defTaille(unsigned int taille){
		this->taille = taille;
	}
	void defStyle(unsigned int style){
		this->style = style;
	}

	void defCouleur(SDL_Color couleur){
		this-> couleur = couleur;
	}


	std::string obtTexte(){ return texte; }
	unsigned int obtTaille(){ return taille; }
	unsigned int obtStyle(){ return style; }
	SDL_Color obtCouleur(){ return couleur; }



};