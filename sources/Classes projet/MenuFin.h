#pragma once
#include "Jeu.h"
#include "Menu.h"
#include "Bouton.h"
#include "Carte.h"
class MenuFin : public Menu {
private:
	Bouton* credits;
	Bouton* nouvellePartie;
	Bouton* menuPrincipal;
	Bouton* quitter;

	bool enCredits;
public:
	MenuFin(void) {
		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Journa2l_000000.png"));

		credits = new Bouton(std::bind(&MenuFin::enClickCredits, this, std::placeholders::_1), std::bind(&MenuFin::survol, this, std::placeholders::_1),
			std::bind(&MenuFin::defaut, this, std::placeholders::_1),
			Vecteur2f(1080, 0),
			new std::string("Credits"), 55);

		nouvellePartie = new Bouton(std::bind(&MenuFin::enClickNouvllePartie, this, std::placeholders::_1), std::bind(&MenuFin::survol, this, std::placeholders::_1),
			std::bind(&MenuFin::defaut, this, std::placeholders::_1),
			Vecteur2f(600, 0),
			new std::string("New Game"), 55);

		menuPrincipal = new Bouton(std::bind(&MenuFin::enClickMenuPrincipal, this, std::placeholders::_1), std::bind(&MenuFin::survol, this, std::placeholders::_1),
			std::bind(&MenuFin::defaut, this, std::placeholders::_1),
			Vecteur2f(300, 0),
			new std::string("Main Menu"), 55);

		quitter = new Bouton(std::bind(&MenuFin::enClickQuitter, this, std::placeholders::_1), std::bind(&MenuFin::survol, this, std::placeholders::_1),
			std::bind(&MenuFin::defaut, this, std::placeholders::_1),
			Vecteur2f(0, 0),
			new std::string("Quit"), 55);

		credits = false;
	}

	void survol(Bouton* sender){
		sender->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* sender){
		sender->defCouleur({ 0, 0, 0, 255 });
	}
	void enClickCredits(void) {
		enCredits = true;
	}

	void enClickNouvllePartie(void) {
		//Carte::obtInstance().
	}

	void enClickMenuPrincipal(void) {
		clic(MENUPRINCIPAL);
	}
	void enClickQuitter(void) {
		GestionnairePhases::obtInstance().viderPhaseActive();
	}

	void remplir(void) {
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(this->spriteFond);
		menuPrincipal->remplir();
		credits->remplir();
		nouvellePartie->remplir();
		quitter->remplir();
	}

	void defPause(bool pause) {
		this->pause = pause;
		if (pause) {
			credits->defEtat(PAUSE);
			nouvellePartie->defEtat(PAUSE);
			menuPrincipal->defEtat(PAUSE);
			quitter->defEtat(PAUSE);
		}

		else {
			credits->defEtat(DEFAUT);
			nouvellePartie->defEtat(DEFAUT);
			menuPrincipal->defEtat(DEFAUT);
			quitter->defEtat(DEFAUT);
		}
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		this->spriteFond->defEchelle(vecteurEchelle);
		credits->defEchelle(vecteurEchelle);
		nouvellePartie->defEchelle(vecteurEchelle);
		menuPrincipal->defEchelle(vecteurEchelle);
		quitter->defEchelle(vecteurEchelle);
	}

	bool obtCredits(void) {
		return enCredits;
	}
};