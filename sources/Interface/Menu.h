class Menu : public Singleton<Menu>{
public:

	bool Actif;
	Sprite2D SpriteFond;
	Etiquette Titre;
	Bouton Retour;

	Menu(bool Actif, Sprite2D SpriteFond, Etiquette Titre, Bouton Retour){
		this->Actif = Actif;
		this->SpriteFond = SpriteFond;
		this->Titre = Titre;
		this->Retour = Retour;
	}

};