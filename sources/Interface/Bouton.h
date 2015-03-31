enum Etat {
	REPOS,SURVOL,CLIQUE
};
#include "Sprite2D.h"
#include "Texte2D.h"
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

	}

	void enSurvol(gfx::Fenetre& fenetre) {
		EtatBouton = SURVOL;
		this->SpriteSurvol.afficher(fenetre);
	}

	void enClique(gfx::Fenetre& fenetre) {
		EtatBouton = CLIQUE;
		this->SpriteClique.afficher(fenetre);
	}

	bool gestEvennement(){
		if (Souris::boutonAppuye(SDL_BUTTON_RIGHT)){
			if ((Souris::obtPosition() >= this->position) && (Souris::obtPosition() <= this->position + this->taille))
			return true;
		}
	}
};