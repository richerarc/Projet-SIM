#pragma once
#include "Singleton.h"
#include "ControleVisuel.h"
#include "Bouton.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire2D.h"

class Menu {

protected:

	gfx::Sprite2D* SpriteFond;
	Etiquette* Titre;
	Bouton* Retour;

public:
	virtual void actualiser() = 0;

};