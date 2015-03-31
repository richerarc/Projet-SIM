#pragma once
#include "Objet.h"
#include <list>
#include "Physique.h"
#include "ObjetInteractif.h"

class ObjetMobile : public ObjetInteractif{
public:

	ObjetMobile(gfx::Modele3D modele, unsigned int ID, char* materiaux, double masse, Vecteur3d position, typeObjet type, unsigned int quantite) : ObjetInteractif(modele, ID, materiaux, masse, position, type){
		
	}


	void appliquerAction(typeAction action){
		switch (type){
		case Autre:
			switch (action){
			case Prendre:
				break;
			}
			break;
		}
	}
};