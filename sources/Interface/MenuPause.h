#pragma once
#include "Menu.h"
#include "Sprite2D.h"
#include "GestionnairePhases.h"


class MenuPause : public Menu {

private:
	gfx::Texte2D* retourJeu;
	gfx::Texte2D* options;
	gfx::Sprite2D* spriteFond;

public:
	MenuPause(void) : Menu() {
		retourJeu = new gfx::Texte2D("Back", "arial.ttf", 9, Vecteur2f(150, 400));
		options = new gfx::Texte2D("Options", "arial.ttf", 9, Vecteur2f(400, 400));
		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("spriteFondMenuPause"));
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(retourJeu);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(options);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteFond);
	}
	~MenuPause(){
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void actualiser(){
		if (retourJeu->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)){
			GestionnairePhases::obtInstance().retirerPhase();
			//GestionnairePhases::obtInstance().ajouterPhase(Phase)
		}
		if (options->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)){
			GestionnairePhases::obtInstance().retirerPhase();
			//GestionnairePhases::obtInstance().ajouterPhase(Phase)
		}
		if (spriteFond->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)){
			GestionnairePhases::obtInstance().retirerPhase();
			//GestionnairePhases::obtInstance().ajouterPhase(Phase)
		}
	}



};