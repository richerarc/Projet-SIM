#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Objet2D.h"
#include "Vecteur3.h"

class Texte2D : public Objet2D{
public:
	std::string texte;
	unsigned int taille;
	SDL_Color couleur;
	SDL_Surface* surface;
	TTF_Font* police;

	Texte2D(Vecteur3f position) : Objet2D(position){}

	Texte2D(const std::string &texte,const char* pathPolice, unsigned int taille, Vecteur3f position) : Objet2D(position){
		this->texte = texte;
		police = TTF_OpenFont(pathPolice, taille);
		this->taille = taille;
		couleur = {0,0,0};
	}
	~Texte2D(){
		if (surface != nullptr){
			SDL_FreeSurface(surface);
			surface = nullptr;
		}
		TTF_CloseFont(police);
	}
	void chargerSurface(){
		surface = TTF_RenderText_Solid(police,texte.c_str(),couleur);
	}
	void defTexte(const std::string &texte){
		this->texte = texte;
	}
	void defPolice(const char* pathPolice){
		police = TTF_OpenFont(pathPolice, taille);
	}
	void defTaille(unsigned int taille){
		this->taille = taille;
	}
	void defCouleur(SDL_Color couleur){
		this-> couleur = couleur;
	}
	std::string obtTexte(){ return texte; }
	unsigned int obtTaille(){ return taille; }
	SDL_Color obtCouleur(){ return couleur; }



};