#pragma once
#include "Menu.h"
#include "Sprite2D.h"
#include "PhaseMenuOptions.h"
#include "Bouton.h"


class MenuPause : public Menu {

private:
	
	Bouton* options;
	Bouton* quitter;

public:
	MenuPause(void) : Menu() {

		//this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));
		//gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteFond);
		
		options = new Bouton(std::bind(&MenuPause::enClicOptions, this, std::placeholders::_1),
			std::bind(&MenuPause::survol, this, std::placeholders::_1),
			std::bind(&MenuPause::defaut, this, std::placeholders::_1),
			Vecteur2f(600, 500),
			"Options",
			20);

		quitter = new Bouton(std::bind(&MenuPause::enClicQuitter, this, std::placeholders::_1),
			std::bind(&MenuPause::survol, this, std::placeholders::_1),
			std::bind(&MenuPause::defaut, this, std::placeholders::_1),
			Vecteur2f(450, 200),
			"Quit",
			20);

		retour = new Bouton(std::bind(&MenuPause::enClicRetour, this, std::placeholders::_1),
			std::bind(&MenuPause::survol, this, std::placeholders::_1),
			std::bind(&MenuPause::defaut, this, std::placeholders::_1),
			Vecteur2f(300, 500),
			"Back",
			50);
	
	}

	~MenuPause(){
		gfx::Gestionnaire2D::obtInstance().retObjets({ this->spriteFond });
		delete this->spriteFond;
	}

	void survol(Bouton* sender){
		sender->defCouleur({ 255, 0, 0, 255 });
	}

	void defaut(Bouton* sender){
		sender->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicRetour(Bouton* sender){
	//	GestionnairePhases::obtInstance().retirerPhase();
	//	gfx::Gestionnaire2D::obtInstance().vider();
	//	GestionnairePhases::obtInstance().obtPhase(0)->defPause(false);
	//	SDL_SetRelativeMouseMode(SDL_TRUE);
	//	SDL_ShowCursor(SDL_DISABLE);
	//	gfx::Gestionnaire3D::obtInstance().defFrustum(45, 800.0 / 600.0, 0.99, 1000);
	//	gfx::Gestionnaire3D::obtInstance().obtCamera()->defPause(false);;
	}

	void enClicOptions(Bouton* sender){
	//	GestionnairePhases::obtInstance().obtDerniere()->defPause(true);
	//	gfx::Gestionnaire2D::obtInstance().vider();
	//	GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuOptions());
	}

	void enClicQuitter(Bouton* sender){
	//	GestionnairePhases::obtInstance().retirerPhase();
	//	gfx::Gestionnaire2D::obtInstance().vider();
	//	GestionnairePhases::obtInstance().retirerPhase();
	//	gfx::Gestionnaire3D::obtInstance().vider();
	}

	void remplir() {
		//gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteFond);
		options->remplir();
		retour->remplir();
		quitter->remplir();
	}

};