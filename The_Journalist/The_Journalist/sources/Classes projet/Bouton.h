#pragma once
#include "Texte2D.h"
#include "GestionnaireEvenements.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire2D.h"
#include "Curseur.h"

//#include <SDL2/SDL.h>
#include <functional>

enum Etat{ EN_CLIC, SURVOL, DEFAUT, PAUSE };

class Bouton{ 
private:

	Etat etat;
	gfx::Texte2D* texte;
	std::function<void(Bouton*)> clicRappel;
	std::function<void(Bouton*)> survolRappel;
	std::function<void(Bouton*)> defautRappel;

public:
	Bouton() : Bouton(nullptr, nullptr, nullptr, Vecteur2f(), new std::string("1"), 0){}

	Bouton(std::function<void(Bouton*)> fonctionClic, std::function<void(Bouton*)> fonctionSurvol, std::function<void(Bouton*)> fonctionDefaut, Vecteur2f position, std::string* texte, int taille){
		etat = DEFAUT;
		clicRappel = fonctionClic;
		survolRappel = fonctionSurvol;
		defautRappel = fonctionDefaut;
		this->texte = new gfx::Texte2D(texte, { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", taille), position);
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEBUTTONUP, std::bind(&Bouton::gererClic, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEMOTION, std::bind(&Bouton::gererSurvol, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_CONTROLLERBUTTONUP, std::bind(&Bouton::gererClic, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_CONTROLLERAXISMOTION, std::bind(&Bouton::gererSurvol, this, std::placeholders::_1));
	}

	~Bouton(){
		gfx::Gestionnaire2D::obtInstance().retObjet(texte);
		delete texte;
	}

	void gererClic(SDL_Event &event){
		if (etat != PAUSE) {
			if (texte->obtRectangle().contient(Curseur::obtPosition()) && (event.button.button == SDL_BUTTON_LEFT || event.cbutton.button == SDL_CONTROLLER_BUTTON_A)){
				clicRappel(this);
				if (etat != PAUSE)
					etat = EN_CLIC;
				else
					defautRappel(this);
			}
			else{
				etat = DEFAUT;
			}
		}
	}
	
	void gererSurvol(SDL_Event &event){
		if (etat != PAUSE) {
			if (texte->obtRectangle().contient(Curseur::obtPosition())){
				if (etat != SURVOL)
					survolRappel(this);
				etat = SURVOL;
			}
			else{
				if (etat != DEFAUT)
					defautRappel(this);
				etat = DEFAUT;

			}
		}
	}

	void defEtat(Etat etat) {
		this->etat = etat;
	}

	void defTexte(std::string* texte){
			this->texte->defTexte(texte);
	}

	void defPosition(Vecteur2f &position){
		texte->defPosition(position);
	}

	void defCouleur(SDL_Color couleur){
		texte->defCouleur(couleur);
	}

	void defRappelClic(std::function<void(Bouton*)> fonction){
		this->clicRappel = fonction;
	}

	void defRappelSurvol(std::function<void(Bouton*)> fonction){
		this->survolRappel = fonction;
	}

	void remplir(void) {

		gfx::Gestionnaire2D::obtInstance().ajouterObjet(texte);

	}

	void defEchelle(Vecteur2f vecteurEchelle) {
		texte->defEchelle(vecteurEchelle);
	}

};