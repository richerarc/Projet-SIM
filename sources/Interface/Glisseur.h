#pragma once

class Glisseur : public ControleVisuel {
private:
	bool enMouvement;
	float sourisx, sourisy;
	bool boutonSouris;
	float pourcentage;
	gfx::Sprite2D * spriteGlisseur;
	Vecteur2f posGlisseur;
public:

	Glisseur(gfx::Sprite2D * spriteFond, gfx::Sprite2D * spriteGlisseur, Vecteur2f position, Vecteur2f taille, float pourcentage) : ControleVisuel() {
		if (pourcentage <= 100.0f && pourcentage >= 0.0f) this->pourcentage = pourcentage;
		else this->pourcentage = 100.0f;
		enMouvement = false;
		boutonSouris = false;
		SpriteFond = spriteFond;
		this->spriteGlisseur = spriteGlisseur;
	}

	void defPourcentage(float pourcentage){
		if ((posGlisseur.x <= (position.x + taille.x - 1)) && (posGlisseur.x >= (position.x + 1))) this->pourcentage = pourcentage;
	}
	void augmenter(){
		if (posGlisseur.x <= (position.x + taille.x - 1))
			this->posGlisseur.x++;
	}
	void diminuer(){
		if (posGlisseur.x >= (position.x + 1))
			this->posGlisseur.x--;
	}

	void rafraichirPourcentage(){
		pourcentage = ((posGlisseur.x - position.x) / taille.x) * 100.0;
	}

	void gestEvenement(SDL_Event evenement){

		if ((evenement.button.type = SDL_MOUSEBUTTONDOWN) && (!boutonSouris)){
			sourisx = evenement.button.x; sourisy = evenement.button.y;
			boutonSouris = true;
		}
		if (evenement.button.type = SDL_MOUSEBUTTONDOWN) {
			if (((sourisx > posGlisseur.x) && (sourisx < posGlisseur.x + 20.0)) && ((sourisy > position.y) && (sourisy < position.y + 20.0)))
				enMouvement = true;
		}
		else {
			enMouvement = false;
			boutonSouris = false;
		}
		if (enMouvement){
			if ((sourisx <= (position.x + taille.x)) && (sourisx >= position.x))
				posGlisseur.x = posGlisseur.x + evenement.motion.x;
		}
		rafraichirPourcentage();
	}

	void afficher(){
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(SpriteFond);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteGlisseur);

	}
	Vecteur2f ObtenirPosition(){
		return position;
	}
	Vecteur2f ObtenirTaille(){
		return taille;
	}

};