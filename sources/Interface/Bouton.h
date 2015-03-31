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
	Bouton(Vecteur2f VecteurPosition, Vecteur2f VecteurTaille, gfx::Texte2D Texte, gfx::Sprite2D SpriteFond, gfx::Sprite2D SpriteClique, gfx::Sprite2D SpriteSurvol) : Etiquette(Texte, SpriteFond, VecteurPosition,  VecteurTaille)) {
		EtatBouton = REPOS;
		this->ObtenirPosition() = VecteurPosition;
		this->ObtenirTaille() = VecteurTaille;
		this->Texte = Texte;
		this->SpriteSurvol = SpriteSurvol;
		this->SpriteClique = SpriteClique;
		this->SpriteFond = SpriteFond;

	}

	void enSurvol(void) {
		EtatBouton = SURVOL;
		this->SpriteSurvol.afficher();
	}

	void enClique(void) {
		EtatBouton = CLIQUE;
		this->SpriteClique.afficher();
	}

	bool gestEvennement(){
		if (Souris::boutonAppuye(SDL_button_right)){
			if ((Souris::obtPosition() >= this->Position) && (Souris::obtPosition() <= this->Position + this->Taille))
			return true;
		}
	}
};