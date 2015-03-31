class ControleVisuel{
protected:
	Sprite2D SpriteFond;	
	Vecteur2f position;	
	Vecteur2f taille;


public:
	ControleVisuel(){}
	virtual void afficher() = 0;
	virtual Vecteur2f ObtenirPosition() = 0;
	virtual Vecteur2f ObtenirTaille() = 0;

};