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
		nouvellePartie = new gfx::Texte2D("Nouvelle Partie", "arial.ttf", 50, Vecteur2f(100, 400));
		options = new gfx::Texte2D("Options", "arial.ttf", 50, Vecteur2f(100, 200));
		logo = new gfx::Sprite2D(Vecteur2f(0, 100), &gfx::GestionnaireRessources::obtInstance().obtTexture("Crate.png"));
		this->Retour = new gfx::Texte2D("Quitter", "arial.ttf", 55, Vecteur2f(100, 0));
		this->SpriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ nouvellePartie, options, this->Retour, logo, this->SpriteFond });
	}

	~MenuPrincipal(void) {
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void actualiser(void) {

		if (nouvellePartie->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			nouvellePartie->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuNouvellePartie());
			}
		}
		else{
			nouvellePartie->defCouleur({ 255, 255, 255, 255 });
		}
		if (options->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			options->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().obtDerniere()->defPause(true);
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuOptions());
			}
		}
		else{
			options->defCouleur({ 255, 255, 255, 255 });
		}
		if (this->Retour->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			this->Retour->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
			}
		}
		else{
			this->Retour->defCouleur({ 255, 255, 255, 255 });
		}
	}

};