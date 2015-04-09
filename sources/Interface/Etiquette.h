#pragma once
#include "ControleVisuel.h"

class Etiquette : public ControleVisuel{

protected:
	gfx::Texte2D* Texte;

public:


	Etiquette(gfx::Texte2D* Texte, gfx::Sprite2D* SpriteFond, Vecteur2f VecteurPosition, Vecteur2f VecteurTaille) : ControleVisuel(){
		this->position = VecteurPosition;
		this->Texte = Texte;
		this->SpriteFond = SpriteFond;
		this->taille = VecteurTaille;
		this->SpriteFond->defEchelle(VecteurTaille);
		this->SpriteFond->defPosition(VecteurPosition);
		this->Texte->defPosition(VecteurPosition);
	}

	void afficher(){ //affichage de l'etiquette
		
	}

	Vecteur2f ObtenirPosition(){
		return this->position;
	}

	Vecteur2f ObtenirTaille(){
		return this->taille;
	}
};