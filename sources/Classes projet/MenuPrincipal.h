#pragma once
#include "Menu.h"
#include "Sprite2D.h"
#include "GestionnairePhases.h"
#include "PhaseMenuNouvellePartie.h"
#include "PhaseMenuOptions.h"
#include "PhaseMenuSucces.h"
#include "Bouton.h"


class MenuPrincipal : public Menu {

private:

	Bouton* demarrer;
	Bouton* options;
	Bouton* succes;
	gfx::Sprite2D* logo;

public:

	MenuPrincipal(void) {

		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/fondMenu.png"));
		logo = new gfx::Sprite2D(Vecteur2f(450, 650), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/logo.png"));

		demarrer = new Bouton(std::bind(&MenuPrincipal::enClicDemarrer, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 480),
			new std::string("New Game"), 50);

		options = new Bouton(std::bind(&MenuPrincipal::enClicOptions, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 180),
			new std::string("Options"), 50);

		succes = new Bouton(std::bind(&MenuPrincipal::enClicSucces, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 330),
			new std::string("Achievements"), 50);

		retour = new Bouton(std::bind(&MenuPrincipal::enClicQuitter, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 30),
			new std::string("Quit"), 50);
		defPause(true);
	}

	~MenuPrincipal(void) {
		gfx::Gestionnaire2D::obtInstance().retObjets({ logo, spriteFond });
		delete logo, spriteFond;
	}

	void survol(Bouton* envoi){
		if (pause)
			return;
		envoi->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* envoi){
		if (pause)
			return;
		envoi->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicDemarrer(Bouton* envoi){
		if (pause)
			return;
		demarrer->defCouleur({ 0, 0, 0, 255 });
		clic(MENUNOUVELLEPARTIE);
	}

	void enClicOptions(Bouton* envoi){
		if (pause)
			return;
		options->defCouleur({ 0, 0, 0, 255 });
		clic(MENUOPTIONS);
	}

	void enClicSucces(Bouton* envoi){
		if (pause)
			return;
		float x = 0.;
		float y = 0.;
		for (auto it : GestionnaireSucces::obtInstance().obtListeSucces()){
			if (it->obtAccompli()){
				it->obtTitre()->defCouleur({ 155, 0, 0, 255 });
			}
			else{
				it->obtTitre()->defCouleur({ 200, 200, 200, 255 });
			}
			it->obtTitre()->defPosition(Vecteur2f(x + 30, 650 - y));
			y = y + 60.;
			if (y == 600){
				y = 0.;
				x = x + 400;
			}
			it->obtDescription()->defPosition(Vecteur2f(900, 35));
			//it->obtDescription()->defCouleur({ 0, 0, 0, 255 });
		}
		clic(MENUSUCCES);
	}

	void enClicQuitter(Bouton* envoi){
		if (pause)
			return;
		GestionnairePhases::obtInstance().enleverPhaseActive();
	}

	void remplir(void) {

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, logo });
		demarrer->remplir();
		options->remplir();
		retour->remplir();
		succes->remplir();

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

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		this->spriteFond->defEchelle(vecteurEchelle);
		this->retour->defEchelle(vecteurEchelle);
		demarrer->defEchelle(vecteurEchelle);
		options->defEchelle(vecteurEchelle);
		logo->defEchelle(vecteurEchelle);
		succes->defEchelle(vecteurEchelle);
	}

};