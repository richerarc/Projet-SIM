class ControleVisuel{
protected:
	Texte2D  texte;		//Texte affiché sur le controle si il y a lieu
	Sprite2D sprite;	//Sprite d'animation du controle si il y a lieu (bouton)
	Vecteur2f position;	//Position du controle
	Vecteur2f taille;


	//ces fonctions de bases seront peut-etre nécéssaire pour les controles
	ControleVisuel(){}
	virtual void afficher() = 0;
	virtual void activation() = 0;

};