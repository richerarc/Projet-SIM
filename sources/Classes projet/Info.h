#pragma once
#include "BoiteCollision.h"
struct InfoObjet {
	unsigned int ID;
	Vecteur3d position;
	Vecteur3d direction;
	double rotation;
	char* cheminModele;
	char* cheminTexture;
	int type;
};

struct InfoSalle {
	unsigned int ID;
	unsigned int nbrPorte;
	Vecteur3d echelle;
	char* cheminModele;
	char* cheminTexture;
	std::list<InfoObjet> Objet;
	std::list<BoiteCollision<double>> boitesCollision;
};

struct InfoPuzzle{
	std::list<InfoObjet> objet;
	BoiteCollision<double> boiteCollision;
	bool* entrees;
};