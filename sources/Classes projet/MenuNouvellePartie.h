#pragma once
#include "Menu.h"
#include "Bouton.h"
#include "Sprite2D.h"
#include "GestionnairePhases.h"
#include "PhaseJeu.h"

class MenuNouvellePartie : public Menu {

private:

	gfx::Texte2D* choisirDiff;
	Bouton* facile;
	Bouton* normal;
	Bouton* difficile;


public:

	MenuNouvellePartie(void){
		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));
		choisirDiff = new gfx::Texte2D("Please choose a difficulty", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial50", 50), Vecteur2f(100, 180));
		choisirDiff->defCouleur({ 0, 0, 0, 255 });

		facile = new Bouton(std::bind(&MenuNouvellePartie::enClicFacile, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::survol, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::defaut, this, std::placeholders::_1),
			Vecteur2f(130, 120),
			"Easy", 20);

		normal = new Bouton(std::bind(&MenuNouvellePartie::enClicNormal, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::survol, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::defaut, this, std::placeholders::_1),
			Vecteur2f(330, 120),
			"Normal", 20);

		difficile = new Bouton(std::bind(&MenuNouvellePartie::enClicDifficile, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::survol, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::defaut, this, std::placeholders::_1),
			Vecteur2f(530, 120),
			"Hardcore", 20);

		defPause(true);

	}

	~MenuNouvellePartie(){
		gfx::Gestionnaire2D::obtInstance().retObjets({ this-> spriteFond, choisirDiff});
		delete this->spriteFond , choisirDiff;
	}

	void survol(Bouton* sender){
		sender->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* sender){
		sender->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicFacile(Bouton* sender) {
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().defPhaseActive(0);
	}

	void enClicNormal(Bouton* sender) {
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().defPhaseActive(0);
	}

	void enClicDifficile(Bouton* sender) {
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().defPhaseActive(0);
	}

	void remplir(void) {

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, choisirDiff });
		facile->remplir();
		normal->remplir();
		difficile->remplir();

	}

	void defPause(bool pause) {

		if (pause) {
			this->pause = pause;
			facile->defEtat(PAUSE);
			normal->defEtat(PAUSE);
			difficile->defEtat(PAUSE);
		}

		else {
			this->pause = pause;
			facile->defEtat(DEFAUT);
			normal->defEtat(DEFAUT);
			difficile->defEtat(DEFAUT);
		}
	}

};