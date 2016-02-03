
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
		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/fondMenu.png"));

		options = new Bouton(std::bind(&MenuPause::enClicOptions, this, std::placeholders::_1),
			std::bind(&MenuPause::survol, this, std::placeholders::_1),
			std::bind(&MenuPause::defaut, this, std::placeholders::_1),
			Vecteur2f(600, 500),
			new std::string("Options"),
			50);

		quitter = new Bouton(std::bind(&MenuPause::enClicQuitter, this, std::placeholders::_1),
			std::bind(&MenuPause::survol, this, std::placeholders::_1),
			std::bind(&MenuPause::defaut, this, std::placeholders::_1),
			Vecteur2f(450, 200),
			new std::string("Quit"),
			50);

		this->retour = new Bouton(std::bind(&MenuPause::enClicRetour, this, std::placeholders::_1),
			std::bind(&MenuPause::survol, this, std::placeholders::_1),
			std::bind(&MenuPause::defaut, this, std::placeholders::_1),
			Vecteur2f(300, 500),
			new std::string("Back"),
			50);
		defPause(true);
	}

	~MenuPause(){
		gfx::Gestionnaire2D::obtInstance().retObjets({ this->spriteFond });
		delete this->spriteFond;
	}

	void survol(Bouton* sender){
		if (pause)
			return;
		sender->defCouleur({ 255, 0, 0, 255 });
	}

	void defaut(Bouton* sender){
		if (pause)
			return;
		sender->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicRetour(Bouton* sender){
		if (pause)
			return;
		retour->defCouleur({ 0, 0, 0, 255 });
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().obtPhaseActive()->defPause(true);
		GestionnairePhases::obtInstance().enleverPhaseActive();
		GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);
		gfx::Gestionnaire3D::obtInstance().obtCamera()->deBloquer();
	}

	void enClicOptions(Bouton* sender){
		if (pause)
			return;
		options->defCouleur({ 0, 0, 0, 255 });
		clic(MENUOPTIONS);
	}

	void enClicQuitter(Bouton* sender){
		if (pause)
			return;
		GestionnairePhases::obtInstance().viderPhaseActive();
	}

	void remplir() {
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteFond);
		options->remplir();
		retour->remplir();
		quitter->remplir();
	}
	void defPause(bool pause) {
		if (pause) {
			this->pause = pause;
			quitter->defEtat(PAUSE);
			options->defEtat(PAUSE);
			retour->defEtat(PAUSE);
		}
		else {
			this->pause = pause;
			quitter->defEtat(DEFAUT);
			options->defEtat(DEFAUT);
			retour->defEtat(DEFAUT);
		}
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		options->defEchelle(vecteurEchelle);
		quitter->defEchelle(vecteurEchelle);
		this->spriteFond->defEchelle(vecteurEchelle);
		quitter->defEchelle(vecteurEchelle);
		this->retour->defEchelle(vecteurEchelle);
	}
};