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
	gfx::Sprite2D* logo;
public:
	MenuPrincipal(void) {
		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteFond);

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
		logo = new gfx::Sprite2D(Vecteur2f(190, 530), &gfx::GestionnaireRessources::obtInstance().obtTexture("logo.png"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(logo);
	}

	~MenuPrincipal(void) {
		gfx::Gestionnaire2D::obtInstance().retObjets({ logo, spriteFond });
		delete logo, spriteFond;
	}

	void survol(Bouton* sender){
		sender->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* sender){
		sender->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicDemarrer(Bouton* sender){
		GestionnairePhases::obtInstance().retirerPhase();
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuNouvellePartie());
	}

	void enClicOptions(Bouton* sender){
		GestionnairePhases::obtInstance().obtDerniere()->defPause(true);
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuOptions());
	}

	void enClicQuitter(Bouton* sender){
		GestionnairePhases::obtInstance().retirerPhase();
	}

	void actualiser(void) {

	}

};