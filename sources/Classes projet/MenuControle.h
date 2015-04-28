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

	}

public:

	MenuControle(void) : Menu() {
		char tmp[15];

		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));

		this->retour = new Bouton(std::bind(&MenuControle::enClickRetour, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(530, 0),
			new std::string("Back"), 55);

		this->Enregistrer = new Bouton(std::bind(&MenuControle::enClickEnregistrer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(730, 0),
			new std::string("Save"), 55);

		avancer = new gfx::Texte2D(new std::string("Foward"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 55), Vecteur2f(100, 665));
		ctrlAvancer = new Bouton(std::bind(&MenuControle::enClickAvancer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 665),
			GestionnaireControle::obtInstance().obtTouche(AVANCER), 45);

		reculer = new gfx::Texte2D(new std::string("Backward"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 55), Vecteur2f(100, 597));
		ctrlReculer = new Bouton(std::bind(&MenuControle::enClickReculer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 597),
			GestionnaireControle::obtInstance().obtTouche(RECULER), 45);

		gauche = new gfx::Texte2D(new std::string("Left"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 55), Vecteur2f(100, 529));
		ctrlGauche = new Bouton(std::bind(&MenuControle::enClickGauche, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 529),
			GestionnaireControle::obtInstance().obtTouche(GAUCHE), 45);

		droite = new gfx::Texte2D(new std::string("Right"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 55), Vecteur2f(100, 461));
		ctrlDroite = new Bouton(std::bind(&MenuControle::enClickDroite, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 461),
			GestionnaireControle::obtInstance().obtTouche(DROITE), 45);

		sauter = new gfx::Texte2D(new std::string("Jump"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 55), Vecteur2f(100, 393));
		ctrlSauter = new Bouton(std::bind(&MenuControle::enClickSauter, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 393),
			GestionnaireControle::obtInstance().obtTouche(SAUTER), 45);

		accroupir = new gfx::Texte2D(new std::string("Crouch"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 55), Vecteur2f(100, 325));
		ctrlAccroupir = new Bouton(std::bind(&MenuControle::enClickAccroupir, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 325),
			GestionnaireControle::obtInstance().obtTouche(ACCROUPIR), 45);

		courir = new gfx::Texte2D(new std::string("Run"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 55), Vecteur2f(100, 257));
		ctrlCourir = new Bouton(std::bind(&MenuControle::enClickCourir, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 257),
			GestionnaireControle::obtInstance().obtTouche(COURIR), 45);

		tirer = new gfx::Texte2D(new std::string("Shoot"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 55), Vecteur2f(100, 189));
		ctrlTirer = new Bouton(std::bind(&MenuControle::enClickTirer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 189),
			GestionnaireControle::obtInstance().obtTouche(TIRER), 45);

		utiliser = new gfx::Texte2D(new std::string("Use/Equip"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 55), Vecteur2f(100, 121));
		ctrlUtiliser = new Bouton(std::bind(&MenuControle::enClickUtiliser, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 121),
			GestionnaireControle::obtInstance().obtTouche(UTILISER), 45);

		inventaire = new gfx::Texte2D(new std::string("Inventory"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 55), Vecteur2f(100, 53));
		ctrlInventaire = new Bouton(std::bind(&MenuControle::enClickInventaire, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 53),
			GestionnaireControle::obtInstance().obtTouche(ACCESINVENTAIRE), 45);

		
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
		sender->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* sender){
		sender->defCouleur({ 0, 0, 0, 255 });
	}
	

	void gererEvenement(SDL_Event Event){
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
		GestionnaireControle::obtInstance().lireControle("Controle.txt");
		reinitialiserControle();
		clicRetour();
	}
	void enClickEnregistrer(Bouton* sender) {
		GestionnaireControle::obtInstance().sauvegarderControle("Controle.txt");
	}
	
	void enClickAvancer(Bouton* sender) {
		sender->defTexte(changementTouche);
		action = AVANCER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlAvancer;
	}


	void enClickReculer(Bouton* sender) {
		sender->defTexte(changementTouche);
		action = RECULER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlReculer;
	}
	void enClickGauche(Bouton* sender) {
		sender->defTexte(changementTouche);
		action = GAUCHE;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlGauche;
	}
	void enClickDroite(Bouton* sender) {
		sender->defTexte(changementTouche);
		action = DROITE;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlDroite;
	}
	void enClickSauter(Bouton* sender) {
		sender->defTexte(changementTouche);
		action = SAUTER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlSauter;
	}
	void enClickAccroupir(Bouton* sender) {
		sender->defTexte(changementTouche);
		action = ACCROUPIR;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlAccroupir;
	}
	void enClickCourir(Bouton* sender) {
		sender->defTexte(changementTouche);
		action = COURIR;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlCourir;
	}
	void enClickTirer(Bouton* sender) {
		sender->defTexte(changementTouche);
		action = TIRER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlTirer;
	}
	void enClickUtiliser(Bouton* sender) {
		sender->defTexte(changementTouche);
		action = UTILISER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlUtiliser;
	}
	void enClickInventaire(Bouton* sender) {
		sender->defTexte(changementTouche);
		action = ACCESINVENTAIRE;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlInventaire;
	}


	void remplir(void) {
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, avancer, reculer, gauche, droite, sauter, accroupir, courir, tirer, utiliser, inventaire });
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
		
	}

	void defPause(bool pause) {
		this->pause = pause;
	}
};