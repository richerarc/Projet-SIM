class MenuSon : public Menu {

public:

	Glisseur Volume;


	MenuSon(Glisseur Volume) : Menu(Actif, SpriteFond, Titre, Retour) {

		this->SpriteFond = SpriteFond;
		this->Titre = Titre;
		this->Retour = Retour;

		this->Volume = Volume;

	}


};