#pragma once
#include "Menu.h"
#include "Texte2D.h"
#include "Glisseur.h"

class MenuSon : public Menu {

private:

	gfx::Texte2D* volumeJeu;
	Glisseur* glisseurVolumeJeu;

	gfx::Texte2D* volumeFond;
	Glisseur* glisseurVolumeFond;

public:

	MenuSon(void) : Menu() {

		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));
		volumeJeu = new gfx::Texte2D(new std::string("Game sound"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 35), Vecteur2f(100, 415));
		volumeFond = new gfx::Texte2D(new std::string("Back noice"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 35), Vecteur2f(100, 215));

		glisseurVolumeJeu = new Glisseur(Vecteur2f(100, 400), Vecteur2f(1, 1), 60, std::bind(&MenuSon::glisseurJeu, this, std::placeholders::_1));
		glisseurVolumeFond = new Glisseur(Vecteur2f(100, 200), Vecteur2f(1, 1), 20, std::bind(&MenuSon::glisseurFond, this, std::placeholders::_1));


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

	void glisseurFond(Glisseur* envoi) {

		ControlleurAudio::obtInstance().defVolumeFond((envoi->obtPourcentage() / 100) * 128);
	}

	void glisseurJeu(Glisseur* envoi) {

		ControlleurAudio::obtInstance().defVolumeEffet((envoi->obtPourcentage() / 100) * 128);
	}

	void remplir(void) {

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, volumeJeu, volumeFond });
		glisseurVolumeJeu->remplir();
		glisseurVolumeFond->remplir();
		retour->remplir();

	}

	void defPause(bool pause) {

		this->pause = pause;
		glisseurVolumeJeu->defPause(pause);
		glisseurVolumeFond->defPause(pause);

		if (pause) {
			retour->defEtat(PAUSE);
		}
		else
			retour->defEtat(DEFAUT);

	}

};