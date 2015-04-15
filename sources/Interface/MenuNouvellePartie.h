#pragma once
#include <SDL2\SDL.h>
#include "Menu.h"

class MenuNouvellePartie : public Menu {

private:

	gfx::Texte2D* choisirDiff;
	gfx::Texte2D* facile;
	gfx::Texte2D* normal;
	gfx::Texte2D* difficile;


public:

	MenuNouvellePartie(void){

		choisirDiff = new gfx::Texte2D("Please choose a difficulty.", "arial.ttf", 30, Vecteur2f(100, 100));
		facile = new gfx::Texte2D("Casual.", "arial.ttf", 20, Vecteur2f(100, 100));
		normal = new gfx::Texte2D("Normal.", "arial.ttf", 20, Vecteur2f(100, 120));
		difficile = new gfx::Texte2D("Hardcore.", "arial.ttf", 20, Vecteur2f(100, 120));

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ choisirDiff, facile, normal, difficile });

	}

	~MenuNouvellePartie(){
		gfx::Gestionnaire2D::obtInstance().retObjets({ choisirDiff, facile, normal, difficile });
	}

	void actualiser(){
		if (facile->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)){
			facile->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){

			}
		}
		else{
			facile->defCouleur({ 255, 255, 255, 255 });
		}

		if (normal->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)){
			normal->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){

			}
		}
		else{
			normal->defCouleur({ 255, 255, 255, 255 });
		}

		if (difficile->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)){
			difficile->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){

			}
		}
		else{
			difficile->defCouleur({ 255, 255, 255, 255 });
		}
	}

};