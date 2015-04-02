class Menu : public Singleton<Menu>{
public:

	Sprite2D SpriteFond;
	Etiquette Titre;
	Bouton Retour;

	Menu(Sprite2D SpriteFond, Etiquette Titre, Bouton Retour){
		this->SpriteFond = SpriteFond;
		this->Titre = Titre;
		this->Retour = Retour;
	}

};