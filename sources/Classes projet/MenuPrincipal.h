#pragma once
#include "Menu.h"
#include "Sprite2D.h"
#include "GestionnairePhases.h"
#include "Jeu.h"
#include "PhaseMenuNouvellePartie.h"
#include "PhaseMenuOptions.h"
#include "Glisseur.h"
#include "Bouton.h"


class MenuPrincipal : public Menu {
private:
	Bouton* demarrer;
	Bouton* options;
	Bouton* quitter;
	gfx::Sprite2D* logo;
public:
	MenuPrincipal(void) {
		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteFond);

		demarrer = new Bouton(std::bind(&MenuPrincipal::enClicDemarrer, this, std::placeholders::_1), 
							  std::bind(&MenuPrincipal::survol, this, std::placeholders::_1), 
							  std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1), 
							  Vecteur2f(100, 260),
							  "New Game");
		options = new Bouton(std::bind(&MenuPrincipal::enClicOptions, this, std::placeholders::_1),
							 std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
			                 std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
			                 Vecteur2f(100, 235),
			                 "Options");
		quitter = new Bouton(std::bind(&MenuPrincipal::enClicQuitter, this, std::placeholders::_1),
							 std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
							 std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
							 Vecteur2f(100, 210),
							 "Quit");
		logo = new gfx::Sprite2D(Vecteur2f(100, 350), &gfx::GestionnaireRessources::obtInstance().obtTexture("logo.png"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(logo);
	}

	~MenuPrincipal(void) {
		gfx::Gestionnaire2D::obtInstance().retObjets({ logo, spriteFond });
		delete logo, spriteFond;
	}

	void survol(Bouton* sender){
		sender->defCouleur({ 255, 0, 0, 255 });
	}

	void defaut(Bouton* sender){
		sender->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicDemarrer(Bouton* sender){
		GestionnairePhases::obtInstance().retirerPhase();
		//GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuNouvellePartie());
	}

	void enClicOptions(Bouton* sender){
		GestionnairePhases::obtInstance().retirerPhase();
		//GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuOptions());
	}

	void enClicQuitter(Bouton* sender){
		GestionnairePhases::obtInstance().retirerPhase();
	}

	void actualiser(void) {

	}

};