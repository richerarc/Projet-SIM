
class Glisseur : public ControleVisuel {
private:
	bool enMouvement;
	float pourcentage;
	float tempx, tempy;
	bool boutonSouris;
	Vecteur2f posGlisseur;
public:

	Glisseur(Vecteur2f position, Vecteur2f taille) : ControleVisuel() {
		this->position = position;
		pourcentage = 50;
		this->taille = taille;
		enMouvement = false;
		boutonSouris = false;
	}

	void defPourcentage(float pourcentage){
		this->pourcentage = pourcentage;
	}
	void augmenter(){
		this->pourcentage++;
	}
	void diminuer(){
		this->pourcentage--;
	}

	void rafraichirPourcentageGlisseur(){
		pourcentage = ((posGlisseur.x - position.x) / taille.x) * 100.0;
	}

	bool gestEvenement(SDL_Event evenement){
	
		if ((evenement.button.type = SDL_MOUSEBUTTONDOWN) && (!boutonSouris)){
			tempx = evenement.button.x; tempy = evenement.button.y;
			boutonSouris = true;
		}
		if (evenement.button.type = SDL_MOUSEBUTTONDOWN) {
			if (((tempx > position.x) && (tempx < position.x + 20)) && ((tempx > position.x) && (tempx < position.x + 20)))
				enMouvement = true;
		}
		else {
			enMouvement = false;
			boutonSouris = false;
		}
		if (enMouvement){
			posGlisseur = posGlisseur.x + evenement.motion.xrel;
		}
		rafraichirPourcentageGlisseur();
	}

	void afficher(){

	}
	void activation(){

	}
};