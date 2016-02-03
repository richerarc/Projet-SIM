#pragma once
#include "Menu.h"
#include "GestionnaireControle.h"
#include "GestionnairePhases.h"
#include "Phase.h"
#include "GestionnaireEvenements.h"
#include "Bouton.h"


class MenuControle : public Menu {

private:
	Bouton* Enregistrer;
	std::string* changementTouche;

	gfx::Texte2D* avancer;
	gfx::Texte2D* reculer;
	gfx::Texte2D* droite;
	gfx::Texte2D* gauche;
	gfx::Texte2D* sauter;
	gfx::Texte2D* accroupir;
	gfx::Texte2D* courir;
	gfx::Texte2D* tirer;
	gfx::Texte2D* utiliser;
	gfx::Texte2D* inventaire;
	gfx::Texte2D* deposer;
	gfx::Texte2D* viser;

	Bouton* ctrlAvancer;
	Bouton* ctrlReculer;
	Bouton* ctrlDroite;
	Bouton* ctrlGauche;
	Bouton* ctrlSauter;
	Bouton* ctrlAccroupir;
	Bouton* ctrlCourir;
	Bouton* ctrlTirer;
	Bouton* ctrlUtiliser;
	Bouton* ctrlInventaire;
	Bouton* ctrlDeposer;
	Bouton* ctrlViser;

	Action action;
	Bouton* toucheEnChoix;
	bool enChoixDeTouche;
	bool pause, premierClic;

	void reinitialiserControle() {

		ctrlAvancer->defTexte(GestionnaireControle::obtInstance().obtTouche(AVANCER));
		ctrlReculer->defTexte(GestionnaireControle::obtInstance().obtTouche(RECULER));
		ctrlGauche->defTexte(GestionnaireControle::obtInstance().obtTouche(GAUCHE));
		ctrlDroite->defTexte(GestionnaireControle::obtInstance().obtTouche(DROITE));
		ctrlSauter->defTexte(GestionnaireControle::obtInstance().obtTouche(SAUTER));
		ctrlAccroupir->defTexte(GestionnaireControle::obtInstance().obtTouche(ACCROUPIR));
		ctrlCourir->defTexte(GestionnaireControle::obtInstance().obtTouche(COURIR));
		ctrlUtiliser->defTexte(GestionnaireControle::obtInstance().obtTouche(UTILISER));
		ctrlInventaire->defTexte(GestionnaireControle::obtInstance().obtTouche(ACCESINVENTAIRE));
		ctrlDeposer->defTexte(GestionnaireControle::obtInstance().obtTouche(DEPOSER));
		ctrlViser->defTexte(GestionnaireControle::obtInstance().obtTouche(VISER));

	}

public:

	MenuControle(void) : Menu() {
		char tmp[15];

		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/fondMenu.png"));

		this->retour = new Bouton(std::bind(&MenuControle::enClickRetour, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(530, 0),
			new std::string("Back"), 55);

		this->Enregistrer = new Bouton(std::bind(&MenuControle::enClickEnregistrer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(730, 0),
			new std::string("Save"), 55);

		avancer = new gfx::Texte2D(new std::string("Foward"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(100, 665));
		ctrlAvancer = new Bouton(std::bind(&MenuControle::enClickAvancer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 665),
			GestionnaireControle::obtInstance().obtTouche(AVANCER), 45);

		reculer = new gfx::Texte2D(new std::string("Backward"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(100, 597));
		ctrlReculer = new Bouton(std::bind(&MenuControle::enClickReculer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 597),
			GestionnaireControle::obtInstance().obtTouche(RECULER), 45);

		gauche = new gfx::Texte2D(new std::string("Left"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(100, 529));
		ctrlGauche = new Bouton(std::bind(&MenuControle::enClickGauche, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 529),
			GestionnaireControle::obtInstance().obtTouche(GAUCHE), 45);

		droite = new gfx::Texte2D(new std::string("Right"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(100, 461));
		ctrlDroite = new Bouton(std::bind(&MenuControle::enClickDroite, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 461),
			GestionnaireControle::obtInstance().obtTouche(DROITE), 45);

		sauter = new gfx::Texte2D(new std::string("Jump"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(100, 393));
		ctrlSauter = new Bouton(std::bind(&MenuControle::enClickSauter, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 393),
			GestionnaireControle::obtInstance().obtTouche(SAUTER), 45);

		accroupir = new gfx::Texte2D(new std::string("Crouch"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(100, 325));
		ctrlAccroupir = new Bouton(std::bind(&MenuControle::enClickAccroupir, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 325),
			GestionnaireControle::obtInstance().obtTouche(ACCROUPIR), 45);

		courir = new gfx::Texte2D(new std::string("Run"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(100, 257));
		ctrlCourir = new Bouton(std::bind(&MenuControle::enClickCourir, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 257),
			GestionnaireControle::obtInstance().obtTouche(COURIR), 45);

		tirer = new gfx::Texte2D(new std::string("Action 1"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(100, 189));
		ctrlTirer = new Bouton(std::bind(&MenuControle::enClickTirer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 189),
			GestionnaireControle::obtInstance().obtTouche(TIRER), 45);

		utiliser = new gfx::Texte2D(new std::string("Use/Equip"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(100, 121));
		ctrlUtiliser = new Bouton(std::bind(&MenuControle::enClickUtiliser, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 121),
			GestionnaireControle::obtInstance().obtTouche(UTILISER), 45);

		inventaire = new gfx::Texte2D(new std::string("Inventory"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(100, 53));
		ctrlInventaire = new Bouton(std::bind(&MenuControle::enClickInventaire, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 53),
			GestionnaireControle::obtInstance().obtTouche(ACCESINVENTAIRE), 45);

		deposer = new gfx::Texte2D(new std::string("Drop"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(600, 665));
		ctrlDeposer = new Bouton(std::bind(&MenuControle::enClickDeposer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(900, 665),
			GestionnaireControle::obtInstance().obtTouche(DEPOSER), 45);

		viser = new gfx::Texte2D(new std::string("Action 2"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(600, 597));
		ctrlViser = new Bouton(std::bind(&MenuControle::enClickViser, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(900, 597),
			GestionnaireControle::obtInstance().obtTouche(VISER), 45);


		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_KEYDOWN, std::bind(&MenuControle::gererEvenement, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEBUTTONDOWN, std::bind(&MenuControle::gererEvenement, this, std::placeholders::_1));

		changementTouche = new std::string("Press any key ...");

		defPause(true);
		premierClic = true;
	}
	~MenuControle(void) {
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void survol(Bouton* sender){
		if (pause)
			return;
		sender->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* sender){
		if (pause)
			return;
		sender->defCouleur({ 0, 0, 0, 255 });
	}


	void gererEvenement(SDL_Event Event){
		if (pause)
			return;
		if (enChoixDeTouche) {
			if (Event.type == SDL_MOUSEBUTTONDOWN && premierClic){
				premierClic = false;
			}
			else if (Event.type == SDL_MOUSEBUTTONDOWN && !premierClic){
				GestionnaireControle::obtInstance().definirControle(action, SOURIS, Event.button.button);
				premierClic = true;
				enChoixDeTouche = false;
				toucheEnChoix->defTexte(GestionnaireControle::obtInstance().obtTouche(action));
				toucheEnChoix = nullptr;
			}
			else{
				GestionnaireControle::obtInstance().definirControle(action, CLAVIER, Event.key.keysym.sym);
				enChoixDeTouche = false;
				toucheEnChoix->defTexte(GestionnaireControle::obtInstance().obtTouche(action));
				toucheEnChoix = nullptr;
			}
		}
	}

	void enClickRetour(Bouton* sender) {
		if (pause)
			return;
		GestionnaireControle::obtInstance().lireControle("Ressources/Info/Controle.txt");
		reinitialiserControle();
		clicRetour();
	}
	void enClickEnregistrer(Bouton* sender) {
		if (pause)
			return;
		GestionnaireControle::obtInstance().sauvegarderControle("Ressources/Info/Controle.txt");
	}

	void enClickAvancer(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = AVANCER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlAvancer;
	}


	void enClickReculer(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = RECULER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlReculer;
	}
	void enClickGauche(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = GAUCHE;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlGauche;
	}
	void enClickDroite(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = DROITE;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlDroite;
	}
	void enClickSauter(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = SAUTER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlSauter;
	}
	void enClickAccroupir(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = ACCROUPIR;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlAccroupir;
	}
	void enClickCourir(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = COURIR;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlCourir;
	}
	void enClickTirer(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = TIRER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlTirer;
	}
	void enClickUtiliser(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = UTILISER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlUtiliser;
	}
	void enClickInventaire(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = ACCESINVENTAIRE;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlInventaire;
	}

	void enClickDeposer(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = DEPOSER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlDeposer;
	}

	void enClickViser(Bouton* sender) {
		if (pause)
			return;
		sender->defTexte(changementTouche);
		action = VISER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlViser;
	}


	void remplir(void) {
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, avancer, reculer, gauche, droite, sauter, accroupir, courir, tirer, utiliser, inventaire, viser, deposer });
		this->retour->remplir();
		this->Enregistrer->remplir();
		ctrlAvancer->remplir();
		ctrlReculer->remplir();
		ctrlGauche->remplir();
		ctrlDroite->remplir();
		ctrlSauter->remplir();
		ctrlAccroupir->remplir();
		ctrlCourir->remplir();
		ctrlTirer->remplir();
		ctrlUtiliser->remplir();
		ctrlInventaire->remplir();
		ctrlDeposer->remplir();
		ctrlViser->remplir();

	}

	void defPause(bool pause) {
		this->pause = pause;
		if (pause) {
			ctrlAvancer->defEtat(PAUSE);
			ctrlReculer->defEtat(PAUSE);
			ctrlDroite->defEtat(PAUSE);
			ctrlGauche->defEtat(PAUSE);
			ctrlSauter->defEtat(PAUSE);
			ctrlAccroupir->defEtat(PAUSE);
			ctrlCourir->defEtat(PAUSE);
			ctrlTirer->defEtat(PAUSE);
			ctrlUtiliser->defEtat(PAUSE);
			ctrlInventaire->defEtat(PAUSE);
			Enregistrer->defEtat(PAUSE);
			this->retour->defEtat(PAUSE);
			ctrlDeposer->defEtat(PAUSE);
			ctrlViser->defEtat(PAUSE);
		}

		else {
			ctrlAvancer->defEtat(DEFAUT);
			ctrlReculer->defEtat(DEFAUT);
			ctrlDroite->defEtat(DEFAUT);
			ctrlGauche->defEtat(DEFAUT);
			ctrlSauter->defEtat(DEFAUT);
			ctrlAccroupir->defEtat(DEFAUT);
			ctrlCourir->defEtat(DEFAUT);
			ctrlTirer->defEtat(DEFAUT);
			ctrlUtiliser->defEtat(DEFAUT);
			ctrlInventaire->defEtat(DEFAUT);
			Enregistrer->defEtat(DEFAUT);
			this->retour->defEtat(DEFAUT);
			ctrlDeposer->defEtat(DEFAUT);
			ctrlViser->defEtat(DEFAUT);

		}
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		Enregistrer->defEchelle(vecteurEchelle);
		this->retour->defEchelle(vecteurEchelle);
		this->spriteFond->defEchelle(vecteurEchelle);

		avancer->defEchelle(vecteurEchelle);
		reculer->defEchelle(vecteurEchelle);
		droite->defEchelle(vecteurEchelle);
		gauche->defEchelle(vecteurEchelle);
		sauter->defEchelle(vecteurEchelle);
		accroupir->defEchelle(vecteurEchelle);
		courir->defEchelle(vecteurEchelle);
		tirer->defEchelle(vecteurEchelle);
		utiliser->defEchelle(vecteurEchelle);
		inventaire->defEchelle(vecteurEchelle);
		viser->defEchelle(vecteurEchelle);
		deposer->defEchelle(vecteurEchelle);

		ctrlAvancer->defEchelle(vecteurEchelle);
		ctrlReculer->defEchelle(vecteurEchelle);
		ctrlDroite->defEchelle(vecteurEchelle);
		ctrlGauche->defEchelle(vecteurEchelle);
		ctrlSauter->defEchelle(vecteurEchelle);
		ctrlAccroupir->defEchelle(vecteurEchelle);
		ctrlCourir->defEchelle(vecteurEchelle);
		ctrlTirer->defEchelle(vecteurEchelle);
		ctrlUtiliser->defEchelle(vecteurEchelle);
		ctrlInventaire->defEchelle(vecteurEchelle);
		ctrlDeposer->defEchelle(vecteurEchelle);
		ctrlViser->defEchelle(vecteurEchelle);
	}
};