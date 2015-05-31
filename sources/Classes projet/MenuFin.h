#pragma once
#include "Jeu.h"
#include "Menu.h"
#include "Bouton.h"
#include "Carte.h"
#include "Phase.h"
class MenuFin : public Menu {
private:
	Bouton* credits;
	Bouton* quitter;

	bool enCredits;
	bool perdu;
public:
	MenuFin(void) {
		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources\\Texture\\JournalPerdu.png"));

		credits = new Bouton(std::bind(&MenuFin::enClickCredits, this, std::placeholders::_1),
			std::bind(&MenuFin::survol, this, std::placeholders::_1),
			std::bind(&MenuFin::defaut, this, std::placeholders::_1),
			Vecteur2f(1080, 0),
			new std::string("Credits"), 55);

		quitter = new Bouton(std::bind(&MenuFin::enClickQuitter, this, std::placeholders::_1),
			std::bind(&MenuFin::survol, this, std::placeholders::_1),
			std::bind(&MenuFin::defaut, this, std::placeholders::_1),
			Vecteur2f(0, 0),
			new std::string("Quit"), 55);

		enCredits = false;
		perdu = true;
		defPause(true);
	}

	void survol(Bouton* envoi){
		envoi->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* envoi){
		envoi->defCouleur({ 0, 0, 0, 255 });
	}
	void enClickCredits(Bouton* envoi) {
		enCredits = true;
	}

	void enClickRecommencer(Bouton* envoi) {
		gfx::Gestionnaire2D::obtInstance().vider();


		nouvelle_Partie = true;

		nbrSalle = Carte::obtInstance().nombreDeSalle;

		perdu = true;

	}

	void enClickMenuPrincipal(Bouton* envoi) {
		clic(MENUPRINCIPAL);
		perdu = true;
	}
	void enClickQuitter(Bouton* envoi) {
		GestionnairePhases::obtInstance().viderPhaseActive();
	}

	void remplir(void) {
		if (!perdu) {
			this->spriteFond->defTexture(new gfx::Texture("Ressources\\Texture\\JournalGagner.png"));

		}
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(this->spriteFond);
		credits->remplir();
		quitter->remplir();
	}

	void defPause(bool pause) {
		this->pause = pause;
		if (pause) {
			credits->defEtat(PAUSE);
			quitter->defEtat(PAUSE);
		}

		else {
			credits->defEtat(DEFAUT);
			quitter->defEtat(DEFAUT);
		}
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		this->spriteFond->defEchelle(vecteurEchelle);
		credits->defEchelle(vecteurEchelle);
		quitter->defEchelle(vecteurEchelle);
	}

	bool obtCredits(void) {
		return enCredits;
	}

	void defPerdu(bool perdu) {
		this->perdu = perdu;
	}
};