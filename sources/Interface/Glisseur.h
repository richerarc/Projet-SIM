class Glisseur : public ControleVisuel {
private:
	bool enMouvement;
	float pourcentage;
	float tempx, tempy;
	bool boutonSouris;
	Vecteur2f posGlisseur;
public:

	Glisseur(texte2D texte, sprite2D sprite, Vecteur2f position, Vecteur2f taille, float pourcentage) : ControleVisuel(texte, sprite, position, taille) {
		if (purcentage <= 100.0f && pourcentage >= 0.0f) this->pourcentage = pourcentage;
		else this->pourcentage = 100.0f;
		enMouvement = false;
		boutonSouris = false;
	}

	void defPourcentage(float pourcentage){
		if (purcentage <= 100.0f && pourcentage >= 0.0f) this->pourcentage = pourcentage;
	}
	void augmenter(){
		this->pourcentage++;
	}
	void diminuer(){
		this->pourcentage--;
	}

	void rafraichirPourcentage(){
		pourcentage = ((posGlisseur.x - position.x) / taille.x) * 100.0;
	}

	void gestEvenement(SDL_Event evenement){

		if ((evenement.button.type = SDL_MOUSEBUTTONDOWN) && (!boutonSouris)){
			tempx = evenement.button.x; tempy = evenement.button.y;
			boutonSouris = true;
		}
		if (evenement.button.type = SDL_MOUSEBUTTONDOWN) {
			if (((tempx > position.x) && (tempx < position.x + 20.0)) && ((tempy > position.y) && (tempy < position.y + 20.0)))
				enMouvement = true;
		}
		else {
			enMouvement = false;
			boutonSouris = false;
		}
		if (enMouvement){
			posGlisseur.x = posGlisseur.x + evenement.motion.xrel;
		}
		rafraichirPourcentage();
	}

	void afficher(){
		sprite.afficher(position);
	}
};