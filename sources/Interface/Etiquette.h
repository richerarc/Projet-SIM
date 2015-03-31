class Etiquette : public ControleVisuel{
protected:
	gfx::Texte2D Texte;
public:
	Etiquette(gfx::Texte2D Texte, gfx::Sprite2D Sprite, Vecteur2f VecteurPosition, Vecteur2f VecteurTaille) : ControleVisuel(){
		this->position = VecteurPosition;
		this->Texte = Texte;
		this->SpriteFond = Sprite;
		this->taille = VecteurTaille;
		this->SpriteFond.defEchelle(VecteurTaille);
		this->SpriteFond.defPosition(VecteurPosition);
		this->Texte.defPosition(VecteurPosition);
	}

	void afficher(gfx::Fenetre& fenetre){ //affichage de l'etiquette
		this->SpriteFond.afficher(fenetre);
		this->Texte.afficher(fenetre);
	}

	Vecteur2f ObtenirPosition(){
		return this->position;
	}

	Vecteur2f ObtenirTaille(){
		return this->taille;
	}
};