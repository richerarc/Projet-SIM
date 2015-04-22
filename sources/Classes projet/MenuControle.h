#pragma once
#include "Menu.h"
#include "GestionnaireControle.h"
#include "GestionnairePhases.h"
#include "Phase.h"
#include "GestionnaireEvenements.h"


class MenuControle : public Menu {

private:
	gfx::Texte2D* Enregistrer;


	gfx::Texte2D* Avancer;
	gfx::Texte2D* Reculer;
	gfx::Texte2D* Droite;
	gfx::Texte2D* Gauche;
	gfx::Texte2D* Sauter;
	gfx::Texte2D* Accroupir;
	gfx::Texte2D* Courir;
	gfx::Texte2D* Tirer;
	gfx::Texte2D* Utiliser;
	gfx::Texte2D* Inventaire;

	Bouton* CtrlAvancer;
	Bouton* CtrlReculer;
	Bouton* CtrlDroite;
	Bouton* CtrlGauche;
	Bouton* CtrlSauter;
	Bouton* CtrlAccroupir;
	Bouton* CtrlCourir;
	Bouton* CtrlTirer;
	Bouton* CtrlUtiliser;
	Bouton* CtrlInventaire;

	Action action;
	gfx::Texte2D* toucheEnChoix;
	bool enChoixDeTouche;

public:

	MenuControle(void) : Menu() {

		

	}

	~MenuControle(void) {
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	
	/*
	void gererEvenement(SDL_Event Event){
		if (enChoixDeTouche) {
			toucheEnChoix->defTexte = (char*)Event.key.keysym.sym;
			GestionnaireControle::obtInstance().definirControle(action, Event.key.keysym.sym);
			enChoixDeTouche = false;
			toucheEnChoix = nullptr;
		}
	}
	*/
	void remplir(void) {



	}
	


};