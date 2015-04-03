class MenuOptions : public Menu {

public:

	Bouton Graphique;
	Bouton Son;
	Bouton Controle;

	MenuOptions(Bouton Graphique, Bouton Son, Bouton Controle) : Menu(Actif, SpriteFond, Titre, Retour) {
		
		this->Graphique = Graphique;
		this->Son = Son;
		this->Controle = Controle;

		this->SpriteFond = SpriteFond;
		this->Titre = Titre;
		this->Retour = Retour;



	}


};