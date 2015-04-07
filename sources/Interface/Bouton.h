#pragma once
#include "Etiquette.h"
#include "Sprite2D.h"
#include "Texte2D.h"


enum Etat {
	REPOS, SURVOL, CLIQUE
};


class Bouton : public Etiquette {
private:
	Etat EtatBouton;
	gfx::Sprite2D SpriteSurvol;
	gfx::Sprite2D SpriteClique;

public:
	Bouton(Vecteur2f VecteurPosition, Vecteur2f VecteurTaille, gfx::Texte2D Texte, gfx::Sprite2D SpriteFond, gfx::Sprite2D SpriteClique, gfx::Sprite2D SpriteSurvol) : Etiquette(Texte, SpriteFond, VecteurPosition,  VecteurTaille) {
		EtatBouton = REPOS;
		this->ObtenirPosition() = VecteurPosition;
		this->ObtenirTaille() = VecteurTaille;
		this->Texte = Texte;
		this->SpriteSurvol = SpriteSurvol;
		this->SpriteClique = SpriteClique;
		this->SpriteFond = SpriteFond;

		this->SpriteFond.obtTexture()->obtSurface()->h = VecteurTaille.y;
		this->SpriteFond.obtTexture()->obtSurface()->w = VecteurTaille.x;
		this->SpriteSurvol.obtTexture()->obtSurface()->h = VecteurTaille.y;
		this->SpriteSurvol.obtTexture()->obtSurface()->w = VecteurTaille.x;
		this->SpriteClique.obtTexture()->obtSurface()->h = VecteurTaille.y;
		this->SpriteClique.obtTexture()->obtSurface()->w = VecteurTaille.x;

	}

	void enSurvol(void) {
		EtatBouton = SURVOL;
		
	}

	void enClique(void) {
		EtatBouton = CLIQUE;
	}

	bool gestEvennement(){
		if (Souris::boutonAppuye(SDL_BUTTON_RIGHT)){
			if ((Souris::obtPosition() >= this->position) && (Souris::obtPosition() <= this->position + this->taille))
			return true;
		}
	}
};