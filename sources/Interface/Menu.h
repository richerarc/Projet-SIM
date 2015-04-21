#pragma once
#include "ControleVisuel.h"
#include "Texte2D.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire2D.h"

class Menu {

protected:

	gfx::Sprite2D* SpriteFond;
	gfx::Texte2D* Retour;

public:
	virtual void actualiser() = 0;

};