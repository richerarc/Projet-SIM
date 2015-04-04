class MenuNouvellePartie : public Menu {

public:

	Etiquette ChoisirDiff;
	Botuon Facile;
	Bouton Normal;
	Bouton Difficile;


	MenuNouvellePartie(Etiquette ChoisirDiff, Bouton Facile, Bouton Normal, Bouton Difficile) : Menu(Actif, SpriteFond, Titre, Retour) {

		this->SpriteFond = SpriteFond;
		this->Titre = Titre;
		this->Retour = Retour;

		this->ChoisirDiff = ChoisirDiff;
		this->Facile = Facile;
		this->Normal = Normal;
		this->Difficile = Difficile;

	}


};