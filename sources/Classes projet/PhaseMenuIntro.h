#pragma once
#include "Phase.h"
#include "MenuIntro.h"
class PhaseMenuIntro : public Phase {
private :
	Chrono* tempsDesYeux;
	MenuIntro* menuIntro;
	bool retirerNoir;
public:
	PhaseMenuIntro(void) : Phase() {
		menuIntro = new MenuIntro();
		retirerNoir = false;
		
	}

	~PhaseMenuIntro() {

		delete menuIntro;
	}

	void rafraichir(float frameTime) {
		/*if (tempsDesYeux->obtTempsEcoule().enSecondes() < 2) {
			if (tempsDesYeux->obtTempsEcoule().enSecondes() < 1) {
				menuIntro->obtSpriteNoirHaut()->defPosition(Vecteur2f(menuIntro->obtSpriteNoirHaut()->obtPosition().x, menuIntro->obtSpriteNoirHaut()->obtPosition().y + (frameTime * 360)));
				menuIntro->obtSpriteNoirBas()->defPosition(Vecteur2f(menuIntro->obtSpriteNoirBas()->obtPosition().x, menuIntro->obtSpriteNoirBas()->obtPosition().y - (frameTime * 360)));
			}
			else {
				menuIntro->obtSpriteNoirHaut()->defPosition(Vecteur2f(menuIntro->obtSpriteNoirHaut()->obtPosition().x, menuIntro->obtSpriteNoirHaut()->obtPosition().y - (frameTime * 360)));
				menuIntro->obtSpriteNoirBas()->defPosition(Vecteur2f(menuIntro->obtSpriteNoirBas()->obtPosition().x, menuIntro->obtSpriteNoirBas()->obtPosition().y + (frameTime * 360)));
			}

		}
		else {
			if (!retirerNoir) {
				gfx::Gestionnaire2D::obtInstance().retObjets({ menuIntro->obtSpriteNoirHaut(), menuIntro->obtSpriteNoirBas() });
				retirerNoir = true;
				menuIntro->obtSpriteFond()->defTexture(new gfx::Texture("Journa2l_000000.png"));
			}
		}*/

	}

	void remplir() {

		menuIntro->remplir();

	}
	void defPause(bool pause) {
		if (!pause)
			tempsDesYeux = new Chrono();
		menuIntro->defPause(pause);
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		menuIntro->actualiserEchelle(vecteurEchelle);
	}

};