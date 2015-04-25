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
	bool pause;

public:

	MenuControle(void) : Menu() {
		char tmp[15];

		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));

		this->retour = new Bouton(std::bind(&MenuControle::enClickRetour, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(500, 0),
			"Back", 55);

		this->Enregistrer = new Bouton(std::bind(&MenuControle::enClickEnregistrer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(700, 0),
			"Save", 55);

		char* g = new char();
		char* h = GestionnaireControle::obtInstance().conversionAsciiAChar(GestionnaireControle::obtInstance().obtenirControles()[AVANCER]);

		avancer = new gfx::Texte2D("Foward", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial55", 55), Vecteur2f(300, 700));
		ctrlAvancer = new Bouton(std::bind(&MenuControle::enClickAvancer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(500, 700),
			GestionnaireControle::obtInstance().conversionAsciiAChar(GestionnaireControle::obtInstance().obtenirControles()[AVANCER]), 55);

		reculer = new gfx::Texte2D("Backward", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial55", 55), Vecteur2f(300, 687));
		ctrlReculer = new Bouton(std::bind(&MenuControle::enClickReculer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(700, 687),
			new char(GestionnaireControle::obtInstance().obtenirControles()[RECULER]), 55);

		gauche = new gfx::Texte2D("Left", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial55", 55), Vecteur2f(100, 619));
		ctrlGauche = new Bouton(std::bind(&MenuControle::enClickGauche, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 619),
			new char(GestionnaireControle::obtInstance().obtenirControles()[GAUCHE]), 55);

		droite = new gfx::Texte2D("Right", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial55", 55), Vecteur2f(100, 551));
		ctrlDroite = new Bouton(std::bind(&MenuControle::enClickDroite, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 551),
			new char(GestionnaireControle::obtInstance().obtenirControles()[DROITE]), 55);

		sauter = new gfx::Texte2D("Jump", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial55", 55), Vecteur2f(100, 483));
		ctrlSauter = new Bouton(std::bind(&MenuControle::enClickSauter, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 483),
			new char(GestionnaireControle::obtInstance().obtenirControles()[SAUTER]), 55);

		accroupir = new gfx::Texte2D("Crouch", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial55", 55), Vecteur2f(100, 415));
		ctrlAccroupir = new Bouton(std::bind(&MenuControle::enClickAccroupir, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 415),
			new char(GestionnaireControle::obtInstance().obtenirControles()[ACCROUPIR]), 55);

		courir = new gfx::Texte2D("Run", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial55", 55), Vecteur2f(100, 347));
		ctrlCourir = new Bouton(std::bind(&MenuControle::enClickCourir, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 347),
			new char(GestionnaireControle::obtInstance().obtenirControles()[COURIR]), 55);

		tirer = new gfx::Texte2D("Shoot", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial55", 55), Vecteur2f(100, 279));
		ctrlTirer = new Bouton(std::bind(&MenuControle::enClickTirer, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 279),
			new char(GestionnaireControle::obtInstance().obtenirControles()[TIRER]), 55);

		utiliser = new gfx::Texte2D("Use/Equip", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial55", 55), Vecteur2f(100, 211));
		ctrlUtiliser = new Bouton(std::bind(&MenuControle::enClickUtiliser, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 211),
			new char(GestionnaireControle::obtInstance().obtenirControles()[UTILISER]), 55);

		inventaire = new gfx::Texte2D("Inventory", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial55", 55), Vecteur2f(100, 143));
		ctrlInventaire = new Bouton(std::bind(&MenuControle::enClickInventaire, this, std::placeholders::_1), std::bind(&MenuControle::survol, this, std::placeholders::_1),
			std::bind(&MenuControle::defaut, this, std::placeholders::_1),
			Vecteur2f(400, 143),
			new char(GestionnaireControle::obtInstance().obtenirControles()[INVENTAIRE]), 55);

		
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_KEYDOWN, std::bind(&MenuControle::gererEvenement, this, std::placeholders::_1));

		defPause(true);
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
			toucheEnChoix->defTexte((char*)Event.key.keysym.sym);
			GestionnaireControle::obtInstance().definirControle(action, Event.key.keysym.sym);
			enChoixDeTouche = false;
			toucheEnChoix = nullptr;
		}
	}

	void enClickRetour(Bouton* sender) {
		//GestionnairePhases::obtInstance().retirerPhase();
		//gfx::Gestionnaire2D::obtInstance().vider();
		//GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuOptions());
	}
	void enClickEnregistrer(Bouton* sender) {
		GestionnaireControle::obtInstance().sauvegarderControle("Francais2.txt");
	}
	
	void enClickAvancer(Bouton* sender) {
		sender->defCouleur({ 215, 110, 75, 255 });
		sender->defTexte("Press any key ...");
		action = AVANCER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlAvancer;
	}


	void enClickReculer(Bouton* sender) {
		sender->defCouleur({ 215, 110, 75, 255 });
		sender->defTexte("Press any key ...");
		action = RECULER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlReculer;
	}
	void enClickGauche(Bouton* sender) {
		sender->defCouleur({ 215, 110, 75, 255 });
		sender->defTexte("Press any key ...");
		action = GAUCHE;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlGauche;
	}
	void enClickDroite(Bouton* sender) {
		sender->defCouleur({ 215, 110, 75, 255 });
		sender->defTexte("Press any key ...");
		action = DROITE;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlDroite;
	}
	void enClickSauter(Bouton* sender) {
		sender->defCouleur({ 215, 110, 75, 255 });
		sender->defTexte("Press any key ...");
		action = SAUTER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlSauter;
	}
	void enClickAccroupir(Bouton* sender) {
		sender->defCouleur({ 215, 110, 75, 255 });
		sender->defTexte("Press any key ...");
		action = ACCROUPIR;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlAccroupir;
	}
	void enClickCourir(Bouton* sender) {
		sender->defCouleur({ 215, 110, 75, 255 });
		sender->defTexte("Press any key ...");
		action = COURIR;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlCourir;
	}
	void enClickTirer(Bouton* sender) {
		sender->defCouleur({ 215, 110, 75, 255 });
		sender->defTexte("Press any key ...");
		action = TIRER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlTirer;
	}
	void enClickUtiliser(Bouton* sender) {
		sender->defCouleur({ 215, 110, 75, 255 });
		sender->defTexte("Press any key ...");
		action = UTILISER;
		enChoixDeTouche = true;
		toucheEnChoix = ctrlUtiliser;
	}
	void enClickInventaire(Bouton* sender) {
		sender->defCouleur({ 215, 110, 75, 255 });
		sender->defTexte("Press any key ...");
		action = INVENTAIRE;
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