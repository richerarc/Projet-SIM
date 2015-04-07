class MenuPrincipal : public Menu {

public:

	Bouton NouvellePartie;
	Bouton Options;


	MenuPrincipal(Bouton NouvellePartie, Bouton Options) : Menu(SpriteFond, Titre, Retour) {

		this->SpriteFond = SpriteFond;
		this->Titre = Titre;
		this->Retour = Retour;

		this->NouvellePartie = NouvellePartie;
		this->Options = Options;

	}


};