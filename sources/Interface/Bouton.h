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
	gfx::Sprite2D* SpriteSurvol;
	gfx::Sprite2D* SpriteClique;

public:
	Bouton(Vecteur2f VecteurPosition, Vecteur2f VecteurTaille, gfx::Texte2D* Texte, gfx::Sprite2D* SpriteFond, gfx::Sprite2D* SpriteClique, gfx::Sprite2D* SpriteSurvol) : Etiquette(Texte, SpriteFond, VecteurPosition, VecteurTaille) {
		EtatBouton = REPOS;
		this->ObtenirPosition() = VecteurPosition;
		this->ObtenirTaille() = VecteurTaille;
		this->Texte = Texte;
		this->SpriteSurvol = SpriteSurvol;
		this->SpriteClique = SpriteClique;
		this->SpriteFond = SpriteFond;

		this->SpriteFond->obtTexture()->obtSurface()->h = VecteurTaille.y;
		this->SpriteFond->obtTexture()->obtSurface()->w = VecteurTaille.x;
		this->SpriteSurvol->obtTexture()->obtSurface()->h = VecteurTaille.y;
		this->SpriteSurvol->obtTexture()->obtSurface()->w = VecteurTaille.x;
		this->SpriteClique->obtTexture()->obtSurface()->h = VecteurTaille.y;
		this->SpriteClique->obtTexture()->obtSurface()->w = VecteurTaille.x;

	}

	void enSurvol(void) {
		if (((Souris::obtPosition().x >= (double)this->position.x) && (Souris::obtPosition().x <= this->position.x + this->taille.x)) &&
			(Souris::obtPosition().y >= (double)this->position.y) && (Souris::obtPosition().y <= this->position.y + this->taille.y)) {
			EtatBouton = SURVOL;
		}

	}

	bool enClique(void) {
		return enSurvol() && Souris::boutonAppuye(SDL)
	}

	void afficher(void) {
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(SpriteSurvol);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(SpriteClique);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(this->SpriteFond);
	}
};