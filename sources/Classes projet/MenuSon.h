#pragma once
#include "Menu.h"
#include "Texte2D.h"
#include "Glisseur.h"

class MenuSon : public Menu {

private:

	gfx::Texte2D* volumeJeu;
	Glisseur* volume;


public:

	MenuSon(void) : Menu() {

		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));
		volumeJeu = new gfx::Texte2D(new std::string("Game sound"), gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial35", 35), Vecteur2f(100, 415));

		volume = new Glisseur(Vecteur2f(100, 400), Vecteur2f(1,1), 50);

		retour = new Bouton(std::bind(&MenuSon::enClicRetour, this, std::placeholders::_1),
			std::bind(&MenuSon::survol, this, std::placeholders::_1),
			std::bind(&MenuSon::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 30),
			new std::string("Return options"), 50);
		defPause(true);

	}

	void survol(Bouton* envoi){
		envoi->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* envoi){
		envoi->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicRetour(Bouton* envoi) {
		clicRetour();
	}

	void remplir(void) {

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, volumeJeu });
		volume->remplir();
		retour->remplir();

	}

	void defPause(bool pause) {

		this->pause = pause;
		volume->defPause(pause);

		if (pause) {
			retour->defEtat(PAUSE);
		}
		else
			retour->defEtat(DEFAUT);

	}

};