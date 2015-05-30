#pragma once
#include "Menu.h"
#include "Texte2D.h"
#include "Bouton.h"

class MenuGraphique : public Menu {

private:

	std::list<gfx::ModeVideo> modesVideo;
	std::list<gfx::ModeVideo>::iterator modeVideo;
	std::list<gfx::ModeVideo>::iterator modeVideoDefaut;
	std::list<gfx::Texte2D*> resolutions;
	std::list<gfx::Texte2D*>::iterator iterateur;
	std::list<gfx::Texte2D*>::iterator resolutionDefaut;
	std::list<gfx::Texte2D*> pleinEcrans;
	std::list<gfx::Texte2D*>::iterator pleinEcranActuel;
	gfx::Texte2D* resolution;
	gfx::Texte2D* pleinEcran;
	Bouton* flecheGauche;
	Bouton* flecheDroite;
	Bouton* flecheGauche2;
	Bouton* flecheDroite2;
	Bouton* appliquer;

	gfx::ModeVideo modeDefaut;

public:

	MenuGraphique(void) : Menu() {
		modeDefaut = gfx::ModeVideo(RESOLUTION_DEFAUT_X, RESOLUTION_DEFAUT_Y);
		std::string* str = new std::string();
		char chr[20];

		for (int i = 0; i < gfx::ModeVideo::obtModes().size() && i < 60; ++i) {
			
			double l = gfx::ModeVideo::obtModes()[i].l;
			double h = gfx::ModeVideo::obtModes()[i].h;

			double fract = l / h;

			if (fract > 1.6 && fract < 1.8) {
				modesVideo.push_back(gfx::ModeVideo::obtModes()[i]);

				str->clear();
				str->append(SDL_itoa(modesVideo.back().l, chr, 10));
				str->append("x");
				str->append(SDL_itoa(modesVideo.back().h, chr, 10));
				resolutions.push_back(new gfx::Texte2D(str, { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 40), Vecteur2f(95, 513)));

				if (modesVideo.back().l == RESOLUTION_DEFAUT_X && modesVideo.back().h == RESOLUTION_DEFAUT_Y) {
					resolutionDefaut = resolutions.end();
					--resolutionDefaut;
					modeVideoDefaut = modesVideo.end();
					--modeVideoDefaut;
				}
			}
		}

		pleinEcrans.push_back(new gfx::Texte2D(new std::string("Windowed"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 40), Vecteur2f(95, 403)));
		pleinEcrans.push_back(new gfx::Texte2D(new std::string("Fullscreen"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 40), Vecteur2f(95, 403)));
		pleinEcrans.push_back(new gfx::Texte2D(new std::string("No border"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 40), Vecteur2f(95, 403)));

		iterateur = resolutionDefaut;
		modeVideo = modeVideoDefaut;
		pleinEcranActuel = pleinEcrans.begin();

		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/fondMenu.png"));
		resolution = new gfx::Texte2D(new std::string("Resolutions"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 40), Vecteur2f(50, 560));
		pleinEcran = new gfx::Texte2D(new std::string("WindowMode"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 40), Vecteur2f(50, 450));

		appliquer = new Bouton(std::bind(&MenuGraphique::enClicAppliquer, this, std::placeholders::_1),
			std::bind(&MenuGraphique::survol, this, std::placeholders::_1),
			std::bind(&MenuGraphique::defaut, this, std::placeholders::_1),
			Vecteur2f(200, 30),
			new std::string("Apply"), 50);

		flecheGauche = new Bouton(std::bind(&MenuGraphique::enClicGauche, this, std::placeholders::_1),
			std::bind(&MenuGraphique::survol, this, std::placeholders::_1),
			std::bind(&MenuGraphique::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 500),
			new std::string("<"), 60);

		flecheDroite = new Bouton(std::bind(&MenuGraphique::enClicDroite, this, std::placeholders::_1),
			std::bind(&MenuGraphique::survol, this, std::placeholders::_1),
			std::bind(&MenuGraphique::defaut, this, std::placeholders::_1),
			Vecteur2f(300, 500),
			new std::string(">"), 60);

		flecheGauche2 = new Bouton(std::bind(&MenuGraphique::enClicGauche2, this, std::placeholders::_1),
			std::bind(&MenuGraphique::survol, this, std::placeholders::_1),
			std::bind(&MenuGraphique::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 390),
			new std::string("<"), 60);

		flecheDroite2 = new Bouton(std::bind(&MenuGraphique::enClicDroite2, this, std::placeholders::_1),
			std::bind(&MenuGraphique::survol, this, std::placeholders::_1),
			std::bind(&MenuGraphique::defaut, this, std::placeholders::_1),
			Vecteur2f(300, 390),
			new std::string(">"), 60);
		
		retour = new Bouton(std::bind(&MenuGraphique::enClicRetour, this, std::placeholders::_1),
			std::bind(&MenuGraphique::survol, this, std::placeholders::_1),
			std::bind(&MenuGraphique::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 30),
			new std::string("Back"), 50);
		defPause(true);

	}

	void enClicRetour(Bouton* envoi) {
		if (pause)
			return;
		clicRetour();
		iterateur = resolutionDefaut;
		modeVideo = modeVideoDefaut;
	}

	void enClicDroite(Bouton* envoi) {
		if (pause)
			return;
		gfx::Gestionnaire2D::obtInstance().retObjet((*iterateur));
		
		++iterateur;
		++modeVideo;

		if (iterateur == resolutions.end()) {
			iterateur = resolutions.begin();
			modeVideo = modesVideo.begin();
		}

		gfx::Gestionnaire2D::obtInstance().ajouterObjet((*iterateur));
	}

	void enClicGauche(Bouton* envoi) {
		if (pause)
			return;
		gfx::Gestionnaire2D::obtInstance().retObjet((*iterateur));
		 
		if (iterateur != resolutions.begin()) {
			--iterateur;
			--modeVideo;
		}
		else {
			iterateur = resolutions.end();
			--iterateur;
			modeVideo = modesVideo.end();
			--modeVideo;
		}
		gfx::Gestionnaire2D::obtInstance().ajouterObjet((*iterateur));
	}

	void enClicDroite2(Bouton* envoi) {
		if (pause)
			return;
		gfx::Gestionnaire2D::obtInstance().retObjet((*pleinEcranActuel));

		++pleinEcranActuel;

		if (pleinEcranActuel == pleinEcrans.end()) {
			pleinEcranActuel = pleinEcrans.begin();
		}

		gfx::Gestionnaire2D::obtInstance().ajouterObjet((*pleinEcranActuel));
	}

	void enClicGauche2(Bouton* envoi) {
		if (pause)
			return;
		gfx::Gestionnaire2D::obtInstance().retObjet((*pleinEcranActuel));

		if (pleinEcranActuel != pleinEcrans.begin()) {
			--pleinEcranActuel;
		}
		else {
			pleinEcranActuel = pleinEcrans.end();
			--pleinEcranActuel;
		}
		gfx::Gestionnaire2D::obtInstance().ajouterObjet((*pleinEcranActuel));
	}

	void enClicAppliquer(Bouton* envoi) {
		if (pause)
			return;
		float l = (*modeVideo).l;
		float h = (*modeVideo).h;
		float ratiol = l / modeDefaut.l;
		float ratioh = h / modeDefaut.h;
		resolutionDefaut = iterateur;
		modeVideoDefaut = modeVideo;
		for (auto it : GestionnairePhases::obtInstance().obtListePhases())
			it->actualiserEchelle(Vecteur2f(ratiol, ratioh));
		glViewport(0, 0, modeVideo->l, modeVideo->h);
		fenetre->defModeVideo(gfx::ModeVideo(*modeVideo));
		fenetre->defPleinEcran(false);
		fenetre->defBordure(true);

		if (!strcmp((*pleinEcranActuel)->texte->obtTexte(), "Fullscreen"))
			fenetre->defPleinEcran(true);
		else if (!strcmp((*pleinEcranActuel)->texte->obtTexte(), "No border"))
			fenetre->defBordure(false);
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

	void remplir(void) {

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, resolution, (*iterateur), pleinEcran, (*pleinEcranActuel) });
		retour->remplir();
		flecheDroite->remplir();
		flecheGauche->remplir();
		flecheDroite2->remplir();
		flecheGauche2->remplir();
		appliquer->remplir();

	}
	void defPause(bool pause) {
		this->pause = pause;
		if (pause) {
			retour->defEtat(PAUSE);
			appliquer->defEtat(PAUSE);
			flecheDroite->defEtat(PAUSE);
			flecheGauche->defEtat(PAUSE);
			flecheDroite2->defEtat(DEFAUT);
			flecheGauche2->defEtat(DEFAUT);
		}
		else {
			retour->defEtat(DEFAUT);
			appliquer->defEtat(DEFAUT);
			flecheDroite->defEtat(DEFAUT);
			flecheGauche->defEtat(DEFAUT);
			flecheDroite2->defEtat(DEFAUT);
			flecheGauche2->defEtat(DEFAUT);
		}
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		this->spriteFond->defEchelle(vecteurEchelle);
		this->retour->defEchelle(vecteurEchelle);
		resolution->defEchelle(vecteurEchelle);
		flecheGauche->defEchelle(vecteurEchelle);
		flecheDroite->defEchelle(vecteurEchelle);
		appliquer->defEchelle(vecteurEchelle);
		flecheGauche2->defEchelle(vecteurEchelle);
		flecheDroite2->defEchelle(vecteurEchelle);
		pleinEcran->defEchelle(vecteurEchelle);
		for (auto it : resolutions)
			it->defEchelle(vecteurEchelle);
		for (auto it : pleinEcrans)
			it->defEchelle(vecteurEchelle);
	}

};