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
	virtual void defPause() = 0;

};