#pragma once
#include "Menu.h"
#include "Texte2D.h"

class MenuOptions : public Menu {

private:
	gfx::Texte2D* son;
	gfx::Texte2D* controle;
	gfx::Texte2D* graphique;
public:
	MenuOptions(void) {
		son = new gfx::Texte2D("Sound", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial50", 50), Vecteur2f(50, 450));
		graphique = new gfx::Texte2D("Graphic", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial50", 50), Vecteur2f(50, 300));
		controle = new gfx::Texte2D("Controle", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial50", 50), Vecteur2f(50, 150));
		this->retour = new gfx::Texte2D("Back", gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", "arial50", 50), Vecteur2f(50, 30));
		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ this->spriteFond, son, controle, graphique });
	}

	~MenuOptions(void) {
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void actualiser(void) {

		if (this->son->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			this->son->defCouleur({ 215, 110, 75, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){

			}
		}
		else{
			this->son->defCouleur({ 0, 0, 0, 255 });
		}

		if (this->controle->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			this->controle->defCouleur({ 215, 110, 75, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
			
			}
		}
		else{
			this->controle->defCouleur({ 0, 0, 0, 255 });
		}

		if (this->graphique->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			this->graphique->defCouleur({ 215, 110, 75, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){

			}
		}
		else{
			this->graphique->defCouleur({ 0, 0, 0, 255 });
		}

		if (this->Retour->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			this->Retour->defCouleur({ 215, 110, 75, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().obtDerniere()->defPause(false);
				GestionnairePhases::obtInstance().obtDerniere()->remplir();
			}
		}
		else{
			this->Retour->defCouleur({ 0, 0, 0, 255 });
		}
	}

};