class ControleVisuel{
protected:
	Sprite2D SpriteFond;	
	Vecteur2 position;	
	Vecteur2 taille;


public:
	ControleVisuel(){}
	virtual void afficher() = 0;
	virtual void ObtenirPosition() = 0;
	virtual void ObtenirTaille() = 0;

};