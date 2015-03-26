#pragma once

struct InfoObjet {
	const unsigned int ID;
	const char* cheminFicher;
};

struct InfoSalle {
	const unsigned int ID;
	const unsigned int nbrPorte;
	const char* cheminFicher;
	std::list<InfoObjet> Objet;
	std::list<BoiteCollision> boitesCollision;
};
