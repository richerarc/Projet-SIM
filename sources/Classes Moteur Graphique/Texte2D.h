#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
class Texte2D{
public:
	std::string texte;
	std::string cheminPolice;
	unsigned int style;
	unsigned int taille;
	SDL_Color couleur;
	TTF_Font* police;

	Texte2D(){
	}

	Texte2D(std::string paramTexte, const char* cheminPolice, unsigned int paramTaille, unsigned int paramStyle){
		texte = paramTexte;
		taille = paramTaille;
		police = TTF_OpenFont(cheminPolice ,taille);
		couleur = { 1, 1, 1, 255 };

	}
	~Texte2D(){
		TTF_CloseFont(police);
	}

	void defTexte(std::string paramTexte){
	
	}
	void defPolice(const char* cheminPolice){
		police = TTF_OpenFont(cheminPolice, taille);
	}
	void defTaille(unsigned int paramTaille){
		taille = paramTaille;
	}
	void defStyle(unsigned int paramStyle){
	}

	void defCouleur(SDL_Color paramCouleur){
		couleur = paramCouleur;
	}


	std::string obtTexte(){ return texte; }
	unsigned int obtTaille(){ return taille; }
	unsigned int obtStyle(){ return style; }
	SDL_Color obtCouleur(){ return couleur; }



};