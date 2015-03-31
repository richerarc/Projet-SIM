class ControleVisuel{
protected:
	gfx::Sprite2D SpriteFond;	
	gfx::Vecteur2f position;	
	gfx::Vecteur2f taille;


public:
	ControleVisuel(){}
	virtual void afficher() = 0;
	virtual Vecteur2f ObtenirPosition() = 0;
	virtual Vecteur2f ObtenirTaille() = 0;

};