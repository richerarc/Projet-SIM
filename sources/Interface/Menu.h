#pragma once
#include "Singleton.h"
#include "ControleVisuel.h"
#include "Bouton.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire2D.h"
#include "Glisseur.h"

class Menu {

protected:

	bool Actif;
	gfx::Sprite2D* SpriteFond;
	Etiquette* Titre;
	Bouton* Retour;

public:
	Menu(void){
		
	}
	virtual bool obtActif(void) = 0;
	virtual void defActif(bool Actif) = 0;

};