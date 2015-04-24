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
		
		facile = new Bouton(std::bind(&MenuNouvellePartie::enClicFacile, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::survol, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::defaut, this, std::placeholders::_1),
			Vecteur2f(130, 120),
			new std::string("Easy"), 20);

		normal = new Bouton(std::bind(&MenuNouvellePartie::enClicNormal, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::survol, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::defaut, this, std::placeholders::_1),
			Vecteur2f(330, 120),
			new std::string("Normal"), 20);

		difficile = new Bouton(std::bind(&MenuNouvellePartie::enClicDifficile, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::survol, this, std::placeholders::_1),
			std::bind(&MenuNouvellePartie::defaut, this, std::placeholders::_1),
			Vecteur2f(530, 120),
			new std::string("Hardcore"), 20);

		choisirDiff = new gfx::Texte2D(new std::string("Please choose a difficulty"), gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial50", 50), Vecteur2f(100, 180));
		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));
		choisirDiff->defCouleur({ 0, 0, 0, 255 });

		defPause(true);
	}

	~MenuNouvellePartie(){
		gfx::Gestionnaire2D::obtInstance().retObjets({ choisirDiff});
	}

	void survol(Bouton* envoi){
		envoi->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* envoi){
		envoi->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicFacile(Bouton* envoi) {
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseJeu());
		GestionnairePhases::obtInstance().defPhaseActive(PHASEJEU);
	}

	void enClicNormal(Bouton* envoi) {
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseJeu());
		GestionnairePhases::obtInstance().defPhaseActive(PHASEJEU);
	}

	void enClicDifficile(Bouton* envoi) {
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseJeu());
		GestionnairePhases::obtInstance().defPhaseActive(PHASEJEU);
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