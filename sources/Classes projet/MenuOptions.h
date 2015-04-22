#pragma once
#include "Menu.h"
#include "Texte2D.h"
#include "MenuSon.h"
#include "PhaseMenuSon.h"
#include "PhaseMenuGraphique.h"
#include "Bouton.h"
class MenuOptions : public Menu {
private:
	Bouton* son;
	Bouton* graphique;
	Bouton* controle;
	Bouton* retour;
public:

	MenuOptions(void) {
		this->SpriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(SpriteFond);

		son = new Bouton(std::bind(&MenuOptions::enClicSon, this, std::placeholders::_1),
			std::bind(&MenuOptions::survol, this, std::placeholders::_1),
			std::bind(&MenuOptions::defaut, this, std::placeholders::_1),
			Vecteur2f(100, 235),
			"Sound",
			20);
		graphique = new Bouton(std::bind(&MenuOptions::enClicGraphique, this, std::placeholders::_1),
			std::bind(&MenuOptions::survol, this, std::placeholders::_1),
			std::bind(&MenuOptions::defaut, this, std::placeholders::_1),
			Vecteur2f(150, 235),
			"Graphic",
			20);
		controle = new Bouton(std::bind(&MenuOptions::enClicControle, this, std::placeholders::_1),
			std::bind(&MenuOptions::survol, this, std::placeholders::_1),
			std::bind(&MenuOptions::defaut, this, std::placeholders::_1),
			Vecteur2f(200, 235),
			"Controles",
			20);
		retour = new Bouton(std::bind(&MenuOptions::enClicRetour, this, std::placeholders::_1),
			std::bind(&MenuOptions::survol, this, std::placeholders::_1),
			std::bind(&MenuOptions::defaut, this, std::placeholders::_1),
			Vecteur2f(150,135),
			"Back",
			20);
	}

	~MenuOptions(void) {
		gfx::Gestionnaire2D::obtInstance().retObjets({ this->SpriteFond });
		delete this->SpriteFond;
	}
	void actualiser(void) {
	}
	void survol(Bouton* sender){
		sender->defCouleur({ 255, 0, 0, 255 });
	}
	void defaut(Bouton* sender){
		sender->defCouleur({ 0, 0, 0, 255 });
	}
	void enClicSon(Bouton* sender){
	//	GestionnairePhases::obtInstance().obtDerniere()->defPause(true);
	//	gfx::Gestionnaire2D::obtInstance().vider();
	//	GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuSon());
	}

	void enClicGraphique(Bouton* sender){
		//	GestionnairePhases::obtInstance().obtDerniere()->defPause(true);
		//	gfx::Gestionnaire2D::obtInstance().vider();
		//	GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuGraphique());
	}

	void enClicControle(Bouton* sender){
		//	GestionnairePhases::obtInstance().obtDerniere()->defPause(true);
		//	gfx::Gestionnaire2D::obtInstance().vider();
		//	GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuControle());
	}
	void enClicRetour(Bouton* sender){
		//GestionnairePhases::obtInstance().retirerPhase();
		//gfx::Gestionnaire2D::obtInstance().vider();
		//GestionnairePhases::obtInstance().obtDerniere()->defPause(false);
	}
	
};