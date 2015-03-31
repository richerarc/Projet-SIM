#include "Sprite2D.h"
#include "Texte2D.h"
class Bouton : public Etiquette {
private:
	Sprite2D SpriteSurvol;
	Sprite2D SpriteClique;

public:
	Bouton(Vecteur2f VecteurPosition, Vecteur2f VecteurTaille, Texte2D Texte, Sprite2D SpriteFond, Sprite2D SpriteClique, Sprite2D SpriteSurvol) {
		this->ObtenirPosition() = VecteurPosition;
		this->ObtenirTaille() = VecteurTaille;
		this->Texte = Texte;
		this->SpriteSurvol = SpriteSurvol;
		this->SpriteClique = SpriteClique;
		this->SpriteFond = SpriteFond;

	}

	void enSurvol(void) {
		this->SpriteSurvol.afficher();
	}

	void enClique(void) {
		this->SpriteClique.afficher();
	}
};