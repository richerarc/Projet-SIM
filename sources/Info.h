#pragma once
#include "BoiteCollision"
struct InfoObjet {
	const unsigned int ID;
	Vecteur3d position;
	const char* cheminModele;
	const char* cheminTexture;
	
};

struct InfoSalle {
	const unsigned int ID;
	const unsigned int nbrPorte;
	const char* cheminModele;
	const char* cheminTexture;
	std::list<InfoObjet> Objet;
	std::list<BoiteCollision> boitesCollision;
};
