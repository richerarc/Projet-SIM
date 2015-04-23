#pragma once
#include "Menu.h"
#include "Texte2D.h"
#include "MenuSon.h"
#include "PhaseMenuSon.h"
#include "PhaseMenuGraphique.h"
#include "PhaseMenuControle.h"
#include "Bouton.h"
class MenuOptions : public Menu {
private:

	Bouton* son;
	Bouton* graphique;
	Bouton* controle;
	
public:

	MenuOptions(void) {

		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));

		son = new Bouton(std::bind(&MenuOptions::enClicSon, this, std::placeholders::_1),
			std::bind(&MenuOptions::survol, this, std::placeholders::_1),
			std::bind(&MenuOptions::defaut, this, std::placeholders::_1),
			Vecteur2f(500, 450),
			"Sound",
			50);

		graphique = new Bouton(std::bind(&MenuOptions::enClicGraphique, this, std::placeholders::_1),
			std::bind(&MenuOptions::survol, this, std::placeholders::_1),
			std::bind(&MenuOptions::defaut, this, std::placeholders::_1),
			Vecteur2f(300, 450),
			"Graphic",
			50);

		controle = new Bouton(std::bind(&MenuOptions::enClicControle, this, std::placeholders::_1),
			std::bind(&MenuOptions::survol, this, std::placeholders::_1),
			std::bind(&MenuOptions::defaut, this, std::placeholders::_1),
			Vecteur2f(300, 300),
			"Controles",
			50);

		this->retour = new Bouton(std::bind(&MenuOptions::enClicRetour, this, std::placeholders::_1),
			std::bind(&MenuOptions::survol, this, std::placeholders::_1),
			std::bind(&MenuOptions::defaut, this, std::placeholders::_1),
			Vecteur2f(300,150),
			"Back",
			50);
		defPause(true);
	}

	~MenuOptions(void) {
		gfx::Gestionnaire2D::obtInstance().retObjets({ this->spriteFond });
		delete this->spriteFond;
	}
	
	void survol(Bouton* sender){
		sender->defCouleur({ 255, 0, 0, 255 });
	}

	void defaut(Bouton* sender){
		sender->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicRetour(Bouton* envoi){
//		gfx::Gestionnaire2D::obtInstance().vider();
//		GestionnairePhases::obtInstance().defPhaseActive();
	}

	void enClicSon(Bouton* envoi){
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().defPhaseActive(6);
		GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
	}

	void enClicGraphique(Bouton* envoi){
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().defPhaseActive(2);
	}

	void enClicControle(Bouton* envoi){
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().defPhaseActive(1);
	}

	void remplir(void) {
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteFond);
		son->remplir();
		graphique->remplir();
		controle->remplir();
		retour->remplir();

	}
	void defPause(bool pause) {

		if (pause) {
			this->pause = pause;
			graphique->defEtat(PAUSE);
			son->defEtat(PAUSE);
			controle->defEtat(PAUSE);
			retour->defEtat(PAUSE);
		}

		else {
			this->pause = pause;
			graphique->defEtat(DEFAUT);
			son->defEtat(DEFAUT);
			controle->defEtat(DEFAUT);
			retour->defEtat(DEFAUT);
		}

	}
	
};