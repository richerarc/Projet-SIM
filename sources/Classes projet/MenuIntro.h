#pragma once
#include "Menu.h"
#include "Bouton.h"
#include "Sprite2D.h"
#include "GestionnairePhases.h"
#include "Jeu.h"
class MenuIntro : public Menu {
private :
	Bouton* suivant;
	gfx::Sprite2D* noirHaut;
	gfx::Sprite2D* noirBas;
	bool premierMenu;
public:
	MenuIntro(void) : Menu() {
		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Journa2l_000000.png"));
		
		suivant = new Bouton(std::bind(&MenuIntro::enClickSuivant, this, std::placeholders::_1), std::bind(&MenuIntro::survol, this, std::placeholders::_1),
			std::bind(&MenuIntro::defaut, this, std::placeholders::_1),
			Vecteur2f(1080, 0),
			new std::string("Next"), 55);
		
		premierMenu = true;
	}

	~MenuIntro(void) {
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void survol(Bouton* sender){
		sender->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* sender){
		sender->defCouleur({ 0, 0, 0, 255 });
	}

	

	void enClickSuivant(Bouton* sender) {
		if (!premierMenu) {
			gfx::Gestionnaire2D::obtInstance().vider();
			Carte::obtInstance().creer();
			if (Carte::obtInstance().finChargement) {
				double hAngle;
				Vecteur3d positionJoueur = Carte::obtInstance().debut(hAngle);
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().obtPhaseActive()->defPause(true);
				GestionnairePhases::obtInstance().ajouterPhase(new PhaseJeu(positionJoueur, hAngle));
				GestionnairePhases::obtInstance().defPhaseActive(PHASEJEU);
				Carte::obtInstance().finChargement = false;
				Carte::obtInstance().salleActive->remplir();
			}
			
		}
		
		premierMenu = false;
		suivant->defTexte(new std::string("Start"));
		this->spriteFond->defTexture(new gfx::Texture("Partie2_000000.png"));

	}
	void remplir(void) {
		
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ this->spriteFond });
		
		
		suivant->remplir();
	}

	void defPause(bool pause) {
		this->pause = pause;
		if (pause) {
			suivant->defEtat(PAUSE);
			
		}

		else {
			suivant->defEtat(DEFAUT);
			
		}
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {

		this->spriteFond->defEchelle(vecteurEchelle);
		suivant->defEchelle(vecteurEchelle);
	}
	gfx::Sprite2D* obtSpriteFond(void) {
		return this->spriteFond;
	}

	gfx::Sprite2D* obtSpriteNoirHaut(void) {
		return noirHaut;
	}

	gfx::Sprite2D* obtSpriteNoirBas(void) {
		return noirBas;
	}
};
