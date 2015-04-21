#pragma once 
#include "Texte2D.h"
#include "GestionnaireEvenements.h"

#include <SDL2/SDL.h>
#include <functional>

class Bouton{ 
private:
	enum Etat{ EN_CLIC, SURVOL, DEFAUT };

	Etat etat;
	gfx::Texte2D* texte;
	std::function<void(SDL_Event&)> clicRappel;
	std::function<void(SDL_Event&)> survolRappel;

public:
	Bouton() : Bouton(nullptr, nullptr, Vecteur2f()){}

	Bouton(std::function<void(Bouton*)> fonctionClic, std::function<void(Bouton*)> fonctionSurvol, Vecteur2f &position, const char* texte, int t){
		etat = DEFAUT;
		clicRappel = fonctionClic;
		survolRappel = fonctionSurvol;
		texte = new gfx::Texte2D("", GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 20), 20, Vecteur2f(0, 0));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEBUTTONDOWN, std::bind(&Bouton::gererClic, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEMOTION, std::bind(&Bouton::gererSurvol, this, std::placeholders::_1));
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(texte);
	}

	~Bouton(){
		gfx::Gestionnaire2D::obtInstance().retObjet(texte);
		delete texte;
	}

	void gererClic(SDL_Event &event){
		if (texte->obtRectangle().contient(event.motion.x, event.motion.y)){
			clicRappel(event);
			etat = EN_CLIC;
		}
		else{
			etat = DEFAUT;
		}
	}
	
	void gererSurvol(SDL_Event &event){
		if (texte->obtRectangle().contient(event.motion.x, event.motion.y)){
			if(etat != SURVOL)
				survolRappel(event);
			etat = SURVOL;
		}
		else{
			etat = DEFAUT;
		}
	}

	void defTexte(const char* texte){
		this->texte->defTexte(texte);
	}

	void defPosition(Vecteur2f &position){
		texte->defPosition(position);
	}



	void defCouleur(SDL_Color &couleur){
		texte->defCouleur(couleur);
	}

	void defRappelClic(std::function<void(SDL_Event&)> fonction){
		this->clicRappel = fonction;
	}

	void defRappelSurvol(std::function<void(SDL_Event&)> fonction){
		this->survolRappel = fonction;
	}

};