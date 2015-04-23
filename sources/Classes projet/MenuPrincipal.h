#pragma once
#include "Menu.h"
#include "Sprite2D.h"
#include "GestionnairePhases.h"
#include "PhaseMenuNouvellePartie.h"
#include "PhaseMenuOptions.h"
#include "Bouton.h"


class MenuPrincipal : public Menu {

private:

	Bouton* demarrer;
	Bouton* options;
	gfx::Sprite2D* logo;

public:

	MenuPrincipal(void) {

		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));
		logo = new gfx::Sprite2D(Vecteur2f(600, 700), &gfx::GestionnaireRessources::obtInstance().obtTexture("logo.png"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({spriteFond, logo});

		demarrer = new Bouton(std::bind(&MenuPrincipal::enClicDemarrer, this, std::placeholders::_1), 
							  std::bind(&MenuPrincipal::survol, this, std::placeholders::_1), 
							  std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1), 
							  Vecteur2f(50, 330),
							  "New Game", 50);

		options = new Bouton(std::bind(&MenuPrincipal::enClicOptions, this, std::placeholders::_1),
							 std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
			                 std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
							 Vecteur2f(50, 180),
			                 "Options", 50);

		retour = new Bouton(std::bind(&MenuPrincipal::enClicQuitter, this, std::placeholders::_1),
							 std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
							 std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
							 Vecteur2f(50, 30),
							 "Quit", 50);

	}

	~MenuPrincipal(void) {
		gfx::Gestionnaire2D::obtInstance().retObjets({ logo, spriteFond });
		delete logo, spriteFond;
	}

	void survol(Bouton* envoi){
		envoi->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* envoi){
		envoi->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicDemarrer(Bouton* envoi){
		
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().defPhaseActive(4);
	}

	void enClicOptions(Bouton* envoi){
		
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().defPhaseActive(5);
	}

	void enClicQuitter(Bouton* envoi){
		GestionnairePhases::obtInstance().retirerPhase();
	}

	void remplir(void) {

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, logo });
		demarrer->remplir();
		options->remplir();
		retour->remplir();

	}

	void defPause(bool pause) {

		if (pause) {
			this->pause = pause;
			demarrer->defEtat(PAUSE);
			options->defEtat(PAUSE);
			retour->defEtat(PAUSE);
		}

		else {
			this->pause = pause;
			demarrer->defEtat(DEFAUT);
			options->defEtat(DEFAUT);
			retour->defEtat(DEFAUT);
		}

	}

};