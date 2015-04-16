#pragma once
#include "Menu.h"
#include "Texte2D.h"

class MenuOptions : public Menu {

private:
	gfx::Texte2D* son;
	gfx::Texte2D* controle;
	gfx::Texte2D* graphique;
	gfx::Texte2D* retour;
public:
	MenuOptions(void) {
		son = new gfx::Texte2D("Sound", "arial.ttf", 50, Vecteur2f(100, 400));
		graphique = new gfx::Texte2D("Graphic", "arial.ttf", 50, Vecteur2f(100, 200));
		controle = new gfx::Texte2D("Controle", "arial.ttf", 50, Vecteur2f(400, 200));
		retour = new gfx::Texte2D("Back", "arial.ttf", 50, Vecteur2f(100, 0));
		this->SpriteFond = new gfx::Sprite2D(Vecteur2f(200, 200), &gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ son, controle, retour, graphique, this->SpriteFond });
	}

	~MenuOptions(void) {
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void actualiser(void) {

		/*if (nouvellePartie->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
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

		}
		}
		else{
		options->defCouleur({ 255, 255, 255, 255 });
		}*/
		if (retour->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			retour->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().obtDerniere()->defPause(false);

			}
		}
		else{
			retour->defCouleur({ 255, 255, 255, 255 });
		}
	}

};