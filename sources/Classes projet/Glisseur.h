#pragma once
#include "ControleVisuel.h"
#include "Rect.h"

class Glisseur : public ControleVisuel {
private:
	bool boutonSouris;
	bool pause;
	float pourcentage;
	gfx::Sprite2D * spriteGlisseur;
	std::function<void(Glisseur*)> fonctionGlisseur;

public:

	Glisseur(Vecteur2f position, Vecteur2f taille, float pourcentage, std::function<void(Glisseur*)> fonctionGlisseur) : ControleVisuel() {
		if (pourcentage <= 100.0f && pourcentage >= 0.0f) 
			this->pourcentage = pourcentage;
		else 
			this->pourcentage = 50.0f;
		
		boutonSouris = false;
		this->position = position;
		this->taille = taille;
		
		SpriteFond = new gfx::Sprite2D(position, &gfx::GestionnaireRessources::obtInstance().obtTexture("Barre.png"));
		this->spriteGlisseur = new gfx::Sprite2D(position, &gfx::GestionnaireRessources::obtInstance().obtTexture("Glisseur.png"));
		
		spriteGlisseur->defPosition(Vecteur2f(position.x + SpriteFond->obtRectangle().l * (pourcentage / 100), position.y - SpriteFond->obtRectangle().h));
		SpriteFond->defEchelle(taille);
		spriteGlisseur->defEchelle(taille);

		this->fonctionGlisseur = fonctionGlisseur;

		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEMOTION, std::bind(&Glisseur::gestEvenement, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEBUTTONDOWN, std::bind(&Glisseur::gestEvenement, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEBUTTONUP, std::bind(&Glisseur::gestEvenement, this, std::placeholders::_1));

		pause = false;

	}
	
	void rafraichirPourcentage(){
		pourcentage = ((spriteGlisseur->obtPosition().x - position.x + spriteGlisseur->obtRectangle().l / 2) / SpriteFond->obtRectangle().l) * 100.0;
	}

	void gestEvenement(SDL_Event evenement){

		if (!pause) {

			if (boutonSouris){
				if ((spriteGlisseur->obtPosition().x >= position.x && evenement.motion.xrel <= 0))
					spriteGlisseur->defPosition(Vecteur2f(Curseur::obtPosition().x, spriteGlisseur->obtPosition().y));

				else if ((spriteGlisseur->obtPosition().x <= SpriteFond->obtRectangle().x + SpriteFond->obtRectangle().l - spriteGlisseur->obtRectangle().l  && evenement.motion.xrel >= 0))
					spriteGlisseur->defPosition(Vecteur2f(Curseur::obtPosition().x, spriteGlisseur->obtPosition().y));

				else
					boutonSouris = false;

				rafraichirPourcentage();
				fonctionGlisseur(this);
			}

			if (evenement.button.type == SDL_MOUSEBUTTONDOWN) {
				if (spriteGlisseur->obtRectangle().contient(Curseur::obtPosition()))
					boutonSouris = true;
			}

			if (evenement.button.type == SDL_MOUSEBUTTONUP)
				boutonSouris = false;
		}
	}

	Vecteur2f ObtenirPosition(){
		return position;
	}
	Vecteur2f ObtenirTaille(){
		return taille;
	}

	float obtPourcentage() {
		return pourcentage;
	}

	void remplir(void) {

		gfx::Gestionnaire2D::obtInstance().ajouterObjet(SpriteFond);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteGlisseur);

	}

	void defPause(bool pause) {
		this->pause = pause;
	}

};