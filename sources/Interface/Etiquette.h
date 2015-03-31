class Etiquette : public ControleVisuel{
protected:
	Texte2D Texte;
public:
	Etiquette(Texte2D Texte, Sprite2D Sprite, Vecteur2d VecteurPosition, Vecteur2d VecteurTaille){
		this->position = VecteurPosition;
		this->Texte = Texte;
		this->SpriteFond = Sprite;
		this->taille = VecteurTaille;
		this->SpriteFond.defEchelle(VecteurTaille);
		this->SpriteFond.defPosition(VecteurPosition);
		this->Texte.defPosition(VecteurPosition);
	}

	void afficher(){ //affichage de l'etiquette
		this->SpriteFond.afficher();
		this->Texte.afficher();
	}

	Vecteur2f ObtenirPosition(){
		return this->position;
	}

	Vecteur2f ObtenirTaille(){
		return this->taille;
	}
};