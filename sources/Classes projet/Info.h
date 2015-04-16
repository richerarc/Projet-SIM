#pragma once
#include "BoiteCollision.h"
struct InfoObjet {
	unsigned int ID;
	Vecteur3d position;
	int rotation;
	char* cheminModele;
	char* cheminTexture;

};

struct InfoSalle {
	unsigned int ID;
	unsigned int nbrPorte;
	char* cheminModele;
	char* cheminTexture;
	std::list<InfoObjet> Objet;
	std::list<BoiteCollision<double>> boitesCollision;
};
