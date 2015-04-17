#pragma once
#include "Menu.h"
#include "Sprite2D.h"



class MenuPause : public Menu {

private:
	gfx::Texte2D* retourJeu;
	gfx::Texte2D* options;
	gfx::Sprite2D* spriteFond;

public:
	MenuPause(void) : Menu() {
		retourJeu = new gfx::Texte2D("Back", "arial.ttf", 45, Vecteur2f(180, 400));
		options = new gfx::Texte2D("Options", "arial.ttf", 45, Vecteur2f(430, 400));
		this->Retour = new gfx::Texte2D("Quit", "arial.ttf", 45, Vecteur2f(350, 200));
		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({options, Retour, retourJeu });

	}
	~MenuPause(){
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void actualiser(){
		if (retourJeu->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			retourJeu->defCouleur({ 215, 110, 75, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().obtPhase(0)->defPause(false);
				SDL_SetRelativeMouseMode(SDL_TRUE);
				SDL_ShowCursor(SDL_DISABLE);
				gfx::Gestionnaire3D::obtInstance().defFrustum(45, 800.0 / 600.0, 0.99, 1000);
				gfx::Gestionnaire3D::obtInstance().obtCamera()->defPause(false);
			}
		}
		else{
			retourJeu->defCouleur({ 0, 0, 0, 255 });
		}
		if (options->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			options->defCouleur({ 215, 110, 75, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				//GestionnairePhases::obtInstance().retirerPhase();
				//gfx::Gestionnaire2D::obtInstance().vider();
				//GestionnairePhases::obtInstance().ajouterPhase(Phase)
			}
		}
		else{
			options->defCouleur({ 0, 0, 0, 255 });
		}

		if (Retour->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			Retour->defCouleur({ 215, 110, 75, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire3D::obtInstance().vider();
			}
		}
		else{
			Retour->defCouleur({ 0, 0, 0, 255 });
		}
	}
};