#pragma once
#include "Menu.h"
#include "Sprite2D.h"
#include "GestionnairePhases.h"
#include "Jeu.h"
#include "Texte2D.h"
#include "PhaseMenuNouvellePartie.h"


class MenuPrincipal : public Menu {
private:
	gfx::Texte2D* nouvellePartie;
	gfx::Texte2D* options;
	gfx::Sprite2D* logo;
public:
	MenuPrincipal(void) {
		nouvellePartie = new gfx::Texte2D("New Game", "arial.ttf", 50, Vecteur2f(50, 330));
		options = new gfx::Texte2D("Options", "arial.ttf", 50, Vecteur2f(50, 180));

		logo = new gfx::Sprite2D(Vecteur2f(160, 500), &gfx::GestionnaireRessources::obtInstance().obtTexture("logo.png"));
		this->Retour = new gfx::Texte2D("Quit", "arial.ttf", 55, Vecteur2f(50, 30));

		this->SpriteFond = new gfx::Sprite2D(Vecteur2f(000, 000), &gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ this->SpriteFond, logo, nouvellePartie, options, this->Retour });
	}

	~MenuPrincipal(void) {
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void actualiser(void) {

		if (nouvellePartie->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			nouvellePartie->defCouleur({ 215, 110, 75, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuNouvellePartie());
			}
		}
		else{
			nouvellePartie->defCouleur({ 0, 0, 0, 255 });
		}
		if (options->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			options->defCouleur({ 215, 110, 75, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
			
			}
		}
		else{
			options->defCouleur({ 0, 0, 0, 255 });
		}
		if (this->Retour->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			this->Retour->defCouleur({ 215, 110, 75, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
			}
		}
		else{
			this->Retour->defCouleur({ 0, 0, 0, 255 });
		}
	}

};