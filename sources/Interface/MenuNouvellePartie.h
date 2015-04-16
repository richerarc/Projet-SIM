#pragma once
#include "Menu.h"
#include "Gestionnaire2D.h"

class MenuNouvellePartie : public Menu {

private:

	gfx::Texte2D* choisirDiff;
	gfx::Texte2D* facile;
	gfx::Texte2D* normal;
	gfx::Texte2D* difficile;


public:

	MenuNouvellePartie(void){

		
		facile = new gfx::Texte2D("Easy", "arial.ttf", 20, Vecteur2f(130, 120));
		normal = new gfx::Texte2D("Normal", "arial.ttf", 20, Vecteur2f(330, 120));
		difficile = new gfx::Texte2D("Hardcore", "arial.ttf", 20, Vecteur2f(530, 120));
		choisirDiff = new gfx::Texte2D("Please choose a difficulty", "arial.ttf", 50, Vecteur2f(100, 180));

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ facile, normal, difficile, choisirDiff});

	}

	~MenuNouvellePartie(){
		gfx::Gestionnaire2D::obtInstance().retObjets({ choisirDiff, facile, normal, difficile });
	}

	void actualiser(){
		if (facile->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)){
			facile->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().ajouterPhase(new PhaseJeu());
			}
		}
		else{
			facile->defCouleur({ 255, 255, 255, 255 });
		}

		if (normal->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)){
			normal->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().ajouterPhase(new PhaseJeu());
			}
		}
		else{
			normal->defCouleur({ 255, 255, 255, 255 });
		}

		if (difficile->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)){
			difficile->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().ajouterPhase(new PhaseJeu());
			}
		}
		else{
			difficile->defCouleur({ 255, 255, 255, 255 });
		}
	}

};