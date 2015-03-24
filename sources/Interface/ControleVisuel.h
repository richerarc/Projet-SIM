class ControleVisuel{
protected:
	bool Active; //Determine l'activation du controle
	Texte2D Texte; //Texte affiché sur le controle si il y a lieu
	Sprtie2D Sprite; //Sprite d'animation du controle si il y a lieu (bouton)
	Vecteur2 Position; //Position du controle


	//ces fonctions de bases seront peut-etre nécéssaire pour les controles
	virtual void Afficher() = 0;
	virtual void Activation() = 0;

};