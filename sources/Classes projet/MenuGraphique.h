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
	gfx::Texte2D* resolution;
	Bouton* flecheGauche;
	Bouton* flecheDroite;
	Bouton* appliquer;

	gfx::ModeVideo modeDefaut;

public:

	MenuGraphique(void) : Menu() {
		modeDefaut = gfx::ModeVideo(1366, 768);
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

				if (modesVideo.back().l == 1280 && modesVideo.back().h == 720) {
					resolutionDefaut = resolutions.end();
					--resolutionDefaut;
					modeVideoDefaut = modesVideo.end();
					--modeVideoDefaut;
				}
			}
		}

		iterateur = resolutionDefaut;
		modeVideo = modeVideoDefaut;

		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/fondMenu.png"));
		resolution = new gfx::Texte2D(new std::string("Resolutions"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 40), Vecteur2f(50, 560));

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

	void enClicAppliquer(Bouton* envoi) {
		if (pause)
			return;
		float l = (*modeVideo).l;
		float ratio = modeDefaut.l / l;
		resolutionDefaut = iterateur;
		modeVideoDefaut = modeVideo;
		Rect<float>::defDimension((*modeVideo).l, (*modeVideo).h);
		for (auto it : GestionnairePhases::obtInstance().obtListePhases())
			it->actualiserEchelle(Vecteur2f(ratio, ratio));

		this->spriteFond->defPosModifier();
		fenetre->defModeVideo(gfx::ModeVideo(*modeVideo));
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

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, resolution, (*iterateur) });
		retour->remplir();
		flecheDroite->remplir();
		flecheGauche->remplir();
		appliquer->remplir();

	}
	void defPause(bool pause) {
		this->pause = pause;
		if (pause) {
			retour->defEtat(PAUSE);
			appliquer->defEtat(PAUSE);
			flecheDroite->defEtat(PAUSE);
			flecheGauche->defEtat(PAUSE);
		}
		else {
			retour->defEtat(DEFAUT);
			appliquer->defEtat(DEFAUT);
			flecheDroite->defEtat(DEFAUT);
			flecheGauche->defEtat(DEFAUT);
		}
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		this->spriteFond->defEchelle(vecteurEchelle);
		this->retour->defEchelle(vecteurEchelle);
		resolution->defEchelle(vecteurEchelle);
		flecheGauche->defEchelle(vecteurEchelle);
		flecheDroite->defEchelle(vecteurEchelle);
		appliquer->defEchelle(vecteurEchelle);
	}

};