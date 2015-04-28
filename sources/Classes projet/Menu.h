#pragma once
#include "Texte2D.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire2D.h"
#include "Bouton.h"

class Menu {

protected:

	gfx::Sprite2D* spriteFond;
	Bouton* retour;
	bool pause;

public:
	virtual void remplir() = 0;
	virtual void defPause(bool pause) = 0;
	virtual void actualiserEchelle(Vecteur2f vecteurEchelle) = 0;

	void clic(TypeMenu type) {
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().obtPhaseActive()->defPause(true);
		GestionnairePhases::obtInstance().defPhaseActive(type);
		GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);
		GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
	}

	void clicRetour(void){
		gfx::Gestionnaire2D::obtInstance().vider();
		GestionnairePhases::obtInstance().obtPhaseActive()->defPause(true);
		GestionnairePhases::obtInstance().enleverPhaseActive();
		GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);
		GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
	}

};