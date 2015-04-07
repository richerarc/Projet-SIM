class MenuControle : public Menu {

public:

	Etiquette Avancer;
	Etiquette Reculer;
	Etiquette Droite;
	Etiquette Gauche;
	Etiquette Sauter;
	Etiquette Accroupir;
	Etiquette Courir;
	Etiquette Tirer;
	Etiquette Utiliser;
	Etiquette Inventaire;

	Bouton CtrlAvancer;
	Bouton CtrlReculer;
	Bouton CtrlDroite;
	Bouton CtrlGauche;
	Bouton CtrlSauter;
	Bouton CtrlAccroupir;
	Bouton CtrlCourir;
	Bouton CtrlTirer;
	Bouton CtrlUtiliser;
	Bouton CtrlInventaire;


	MenuControle(Etiquette Avancer, Etiquette Reculer, Etiquette Droite, Etiquette Gauche, Etiquette Sauter, Etiquette Accroupir, Etiquette Courir, Etiquette Tirer, Etiquette Utiliser, Etiquette Inventaire,
				 Bouton CtrlAvancer, Bouton CtrlReculer, Bouton CtrlDroite, Bouton CtrlGauche, Bouton CtrlSauter, Bouton CtrlAccroupir, Bouton CtrlCourir, Bouton CtrlTirer, Bouton CtrlUtiliser, Bouton CtrlInventaire)
				 : Menu(Actif, SpriteFond, Titre, Retour) {

		this->SpriteFond = SpriteFond;
		this->Titre = Titre;
		this->Retour = Retour;

		
		this->Avancer = Avancer;
		this->Reculer = Reculer;
		this->Droite = Droite;
		this->Gauche = Gauche;
		this->Sauter = Sauter;
		this->Accroupir = Accroupir;
		this->Courir = Courir;
		this->Tirer = Tirer;
		this->Utiliser = Utiliser;
		this->Inventaire = Inventaire;

		this->CtrlAvancer = CtrlAvancer;
		this->CtrlReculer = CtrlReculer;
		this->CtrlDroite = CtrlDroite;
		this->CtrlGauche = CtrlGauche;
		this->CtrlSauter = CtrlSauter;
		this->CtrlAccroupir = CtrlAccroupir;
		this->CtrlCourir = CtrlCourir;
		this->CtrlTirer = CtrlTirer;
		this->CtrlUtiliser = CtrlUtiliser;
		this->CtrlInventaire = CtrlInventaire;



	}


};