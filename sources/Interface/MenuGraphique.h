class MenuGraphique : public Menu {

public:

	Etiquette Resolution;
	Bouton FlecheGauche;
	Bouton FlecheDroite;
	Bouton Appliquer;


	MenuGraphique(Etiquette Resolution, Bouton FlecheGauche, Bouton FlecheDroite, Bouton Appliquer) : Menu(Actif, SpriteFond, Titre, Retour) {

		this->SpriteFond = SpriteFond;
		this->Titre = Titre;
		this->Retour = Retour;

		this->Resolution = Resolution;
		this->FlecheGauche = FlecheGauche;
		this->FlecheDroite = FlecheDroite;
		this->Appliquer = Appliquer;

	}


};