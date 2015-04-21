#pragma once
#include "Menu.h"
#include "Sprite2D.h"
#include "GestionnairePhases.h"
#include "Jeu.h"
#include "Texte2D.h"
#include "PhaseMenuNouvellePartie.h"
#include "PhaseMenuOptions.h"
#include "Glisseur.h"
#include "Bouton.h"


class MenuPrincipal : public Menu {
private:
	Bouton* demarrer;
public:
	MenuPrincipal(void) {
		demarrer = new Bouton(std::bind(MenuPrincipal::enClicDemarrer, this, std::placeholders::_1), std::bind(MenuPrincipal::survol, this, std::placeholders::_1));
		
	}

	~MenuPrincipal(void) {
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void survol(Bouton* sender){
		sender->defCouleur({ 255, 0, 0, 255 });
	}

	void enClicDemarrer(Bouton* sender){

	}

	void actualiser(void) {

	}


};