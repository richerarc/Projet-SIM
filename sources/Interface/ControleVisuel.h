class ControleVisuel{
protected:
	Sprite2D SpriteFond;	
	Vecteur2d position;	
	Vecteur2d taille;


public:
	ControleVisuel(){}
	virtual void afficher() = 0;
	virtual Vecteur2d ObtenirPosition() = 0;
	virtual Vecteur2d ObtenirTaille() = 0;

};